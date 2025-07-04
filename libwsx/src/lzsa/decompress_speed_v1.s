//  decompress_speed_v1.S - time-efficient decompressor implementation for 8088
//  NASM syntax.
//
//  Usual DOS assembler SMALL model assumptions apply.  This code:
//  - Assumes it was invoked via NEAR call (change RET to RETF for FAR calls)
//  - Is interrupt-safe
//  - Is not re-entrant (do not decompress while already running decompression)
//  - Trashes all data and segment registers
//
//  Copyright (C) 2019 Jim Leonard, Emmanuel Marty
//  Code modified for Wonderful toolchain
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source distribution.

#include <wonderful.h>
#include "asm-preamble.h"
   .intel_syntax noprefix
   .global wsx_lzsa1_decompress

//  ---------------------------------------------------------------------------
//  Decompress raw LZSA1 block
//  inputs:
//  * ds:si: raw LZSA1 block
//  * es:di: output buffer
//  output:
//  * ax:    decompressed size
//  ---------------------------------------------------------------------------

// Must declare this in the code segment:
#ifndef __IA16_TUNE_NEC_V30MZ
SHR4table:
        .byte 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
        .byte 0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01
        .byte 0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02
        .byte 0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03
        .byte 0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04
        .byte 0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05
        .byte 0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06
        .byte 0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07
#endif

wsx_lzsa1_decompress:
   push si
   push di
   push es
   push ds
   push bp
   mov bp, sp
   mov di, ax
   lds si, [bp+IA16_CALL_STACK_OFFSET(10)]
   mov es, dx

        push    di              //remember decompression offset
        cld                     //ensure string ops move forward
#ifndef __IA16_TUNE_NEC_V30MZ
        mov     bx,offset SHR4table
#endif
        xor     cx,cx

#ifdef __IA16_TUNE_NEC_V30MZ
	.align 2, 0x90
#endif
.decode_token:
        xchg    cx,ax           //clear ah (cx = 0 from match copy's rep movsb)
        lodsb                   //read token byte: O|LLL|MMMM
        mov     dx,ax           //copy our token to dl for later MMMM handling

        and     al,0x70         //isolate literals length in token (LLL)
        jz      .check_offset_size //if LLL=0, we have no literals// goto match
        cmp     al,0x70         //LITERALS_RUN_LEN?
        jne     .got_literals  //no, we have full count from token// go copy

        lodsb                   //grab extra length byte
        add     al,0x7          //add LITERALS_RUN_LEN
        jnc     .got_literals_exact //if no overflow, we have full count
        je      .big_literals

.mid_literals:
        lodsb                   //grab single extra length byte
        inc     ah              //add 256
        xchg    cx,ax           //with longer counts, we can save some time
        shr     cx,1            //by doing a word copy instead of a byte copy.
        rep     movsw           //We don't need to account for overlap because
#ifdef __IA16_TUNE_NEC_V30MZ
        jnc .mid_literals_nobyte
        movsb
.mid_literals_nobyte:
#else
        adc     cx,0            //source for literals isn't the output buffer.
        rep     movsb
#endif
        jmp     .check_offset_size

.big_literals:
        lodsw                   //grab 16-bit extra length
        xchg    cx,ax           //with longer counts, we can save some time
        shr     cx,1            //by doing a word copy instead of a byte copy.
        rep     movsw
#ifdef __IA16_TUNE_NEC_V30MZ
        jnc .big_literals_nobyte
        movsb
.big_literals_nobyte:
#else
        adc     cx,0
        rep     movsb
#endif
        jmp     .check_offset_size

.got_literals:
#ifndef __IA16_TUNE_NEC_V30MZ
        cs   xlat               //shift literals length into place
#else
	// On the NEC V30MZ, XLAT takes 5 cycles, but an immediate shift
	// always takes 3 cycles.
	shr	al, 4
#endif
.got_literals_exact:
        xchg    cx,ax
        rep     movsb           //copy cx literals from ds:si to es:di

.check_offset_size:
        test    dl,dl           //check match offset size in token (O bit)
        js      .get_long_offset //load absolute 16-bit match offset

        mov     ah,0xFF         //set up high byte
        lodsb                   //load low byte

.get_match_length:
        xchg    dx,ax           //dx: match offset  ax: original token
        and     al,0xF          //isolate match length in token (MMMM)
        cmp     al,0xF          //MATCH_RUN_LEN?
        jne     .got_matchlen_short  //no, we have the full match length from the token, go copy

        lodsb                   //grab extra length byte
        add     al,0x12         //add MIN_MATCH_SIZE + MATCH_RUN_LEN
        jnc     .do_long_copy  //if no overflow, we have the entire length
        jne     .mid_matchlen

        lodsw                   //grab 16-bit length
        xchg    cx,ax           //get ready to do a long copy
        jcxz    .done_decompressing //wait, is it the EOD marker? Exit if so
        jmp     .copy_len_preset //otherwise, do the copy

.get_long_offset:
        lodsw                   //Get 2-byte match offset
        jmp     .get_match_length

.got_matchlen_short:
        add     al,3            //add MIN_MATCH_SIZE
        xchg    cx,ax           //copy match length into cx
        mov     bp,ds           //save ds
        mov     ax,es
        mov     ds,ax           //ds=es
#ifdef __IA16_TUNE_NEC_V30MZ
        mov     ax,si           //dx:ax = old ds:si
#else
        xchg    si,ax           //dx:ax = old ds:si
#endif
        mov     si,di           //ds:si now points at back reference in output data
        add     si,dx
        rep     movsb           //copy match
#ifdef __IA16_TUNE_NEC_V30MZ
        mov     si,ax           //restore si
#else
        xchg    si,ax
#endif
        mov     ds,bp           //restore ds
        jmp     .decode_token  //go decode another token

.done_decompressing:
        pop     ax              //retrieve the original decompression offset
        xchg    di,ax           //compute decompressed size
        sub     ax,di
   pop bp
   pop ds
   pop es
   pop di
   pop si
   IA16_RET 0x4

//With a confirmed longer match length, we have an opportunity to optimize for
//the case where a single byte is repeated long enough that we can benefit
//from rep movsw to perform the run (instead of rep movsb).
.mid_matchlen:
        lodsb                   //grab single extra length byte
        inc     ah              //add 256
.do_long_copy:
        xchg    cx,ax           //copy match length into cx
.copy_len_preset:
        push    ds              //save ds
        mov     bp,es
        mov     ds,bp           //ds=es
        mov     bp,si           //save si
        mov     si,di           //ds:si now points at back reference in output data
        add     si,dx
        cmp     dx,-2           //do we have a byte/word run to optimize?
        jae     .do_run        //perform a run
//You may be tempted to change "jae" to "jge" because DX is a signed number.
//Don't!  The total window is 64k, so if you treat this as a signed comparison,
//you will get incorrect results for offsets over 32K.

//If we're here, we have a long copy and it isn't byte-overlapping (if it
//overlapped, we'd be in .do_run_1)  So, let's copy faster with REP MOVSW.
//This won't affect 8088 that much, but it speeds up 8086 and higher.
        shr     cx,1
        rep     movsw
#ifdef __IA16_TUNE_NEC_V30MZ
        jnc .copy_len_preset_nobyte
        movsb
.copy_len_preset_nobyte:
#else
        adc     cx,0
        rep     movsb
#endif
        mov     si,bp           //restore si
        pop     ds
        jmp     .decode_token  //go decode another token

.do_run:
        je      .do_run_2      //fall through to byte (common) if not word run

.do_run_1:
        lodsb                   //load first byte of run into al
        mov     ah,al
        shr     cx,1
        rep     stosw           //perform word run
#ifdef __IA16_TUNE_NEC_V30MZ
        jnc .do_run_1_nobyte
        stosb
.do_run_1_nobyte:
#else
        adc     cx,0
        rep     stosb           //finish word run
#endif
        mov     si,bp           //restore si
        pop     ds
        jmp     .decode_token  //go decode another token

.do_run_2:
        lodsw                   //load first word of run
        shr     cx,1
        rep     stosw           //perform word run
#ifdef __IA16_TUNE_NEC_V30MZ
        jnc .do_run_2_nobyte
        stosb
.do_run_2_nobyte:
#else
        adc     cx,0            //despite 2-byte offset, compressor might
        rep     stosb           //output odd length. better safe than sorry.
#endif
        mov     si,bp           //restore si
        pop     ds
        jmp     .decode_token  //go decode another token

//Speed optimization history (decompression times in microseconds @ 4.77 MHz):
// original E. Marty code    shuttle 123208 alice 65660 robotron 407338 ***
// table for shr al,4        shuttle 120964 alice 63230 robotron 394733 +++
// push/pop to mov/mov       shuttle 118176 alice 61835 robotron 386762 +++
// movsw for literalcpys     shuttle 124102 alice 64908 robotron 400220 --- rb
// stosw for byte runs       shuttle 118897 alice 65040 robotron 403518 --- rb
// better stosw for runs     shuttle 117712 alice 65040 robotron 403343 +--
// disable RLE by default    shuttle 116924 alice 60783 robotron 381226 +++
// optimize got_matchlen     shuttle 115294 alice 59588 robotron 374330 +++
// fall through to getML     shuttle 113258 alice 59572 robotron 372004 +++
// fall through to midLI     shuttle 113258 alice 59572 robotron 375060 ..- rb
// fall through midMaLen     shuttle 113247 alice 59572 robotron 372004 +.+
// movsw for litlen > 255    shuttle 113247 alice 59572 robotron 371612 ..+
// rep stosw for long runs   shuttle 113247 alice 59572 robotron 371612 ...
// rep movsw for long cpys   shuttle 113247 alice 59572 robotron 371035 ..+
// xchg/dec ah -> mov ah,val shuttle 112575 alice 59272 robotron 369198 +++
// force >12h len.to longcpy shuttle 101998 alice 59266 robotron 364459 +.+
// more efficient run branch shuttle 102239 alice 59297 robotron 364716 --- rb
// even more eff. run branch shuttle 101998 alice 59266 robotron 364459 ***
// BUGFIX - bad sign compare shuttle 101955 alice 59225 robotron 364117 +++
// reverse 16-bit len compar shuttle 102000 alice 59263 robotron 364460 --- rb
// jcxz for EOD detection    no change to speed, but is 1 byte shorter  +++
// force movsw for literals  shuttle 107183 alice 62555 robotron 379524 --- rb
// defer shr4 until necessry shuttle 102069 alice 60236 robotron 364096 ---
// skip literals if LLL=0    shuttle  98655 alice 57849 robotron 363358 ---
// fall through to mid_liter shuttle  98595 alice 57789 robotron 361998 +++
// == jumptable experiments begin ==
// jumptable for small copys shuttle 101594 alice 61078 robotron 386018 ---
// start:xchg instead of mov shuttle 100948 alice 60467 robotron 381112 +++
// use table for LLL=0 check shuttle 106972 alice 63333 robotron 388304 --- rb
// jmptbl to fallthrough mov shuttle 102532 alice 60760 robotron 383070 ---
// cpy fallthrough check_ofs shuttle  98939 alice 58917 robotron 371019 +**
// single jumptable jump     shuttle  97528 alice 57264 robotron 362194 ++*
// conditional check for L=7 shuttle  98610 alice 58521 robotron 368153 --- rb
// rip out the jumptable :-/ shuttle  97616 alice 57128 robotron 360697 +++
// defer add MIN_MATCH_SIZE  shuttle  97250 alice 57004 robotron 361191 ++?
// cache constants in regs   shuttle 104681 alice 59939 robotron 380125 --- rb
