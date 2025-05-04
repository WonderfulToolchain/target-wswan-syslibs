/**
 * Copyright (c) 2023, 2024 Adrian "asie" Siekierka
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
*/

#include <wonderful.h>
#include <ws.h>
#include "asm-preamble.h"
	.intel_syntax noprefix

    .global text_get_fontdata
text_get_fontdata:
    push ds
    push es
    push si
    push di

    mov bl, [__wwcl_text_mode]

    push cs
    pop ds

    mov di, dx
    mov es, cx

    cmp bl, 1
    ja .no_ascii
    cmp ax, 0x0080
    jb .ascii
    cmp bl, 1
.no_ascii:
    jb .no_sjis

#ifndef __IA16_CMODEL_TINY__
    call text_sjis_default_font_handler
    mov ax, 0
    jnc .sjis_continue
#endif
.no_sjis:
    mov ax, 0x8000
    jmp .finish

.sjis_continue:
    mov ds, cx

.copy:
    cld
    // copy DS:SI => ES:DI
    movsw
    movsw
    movsw
    movsw

.finish:
    pop di
    pop si
    pop es
    pop ds

    IA16_RET

.ascii:
    mov si, offset __wwcl_font_ank
    shl ax, 3
    add si, ax

    xor ax, ax
    jmp .copy

#ifndef __IA16_CMODEL_TINY__
    // input: AX - Shift-JIS character code
    // output: CX:SI - font data location
    // output: carry - set if no data found
text_sjis_default_font_handler:
    push bx
    push dx
    push ds

    mov si, offset __wwcl_font_sjis
    push si
    mov dx, ax

.loop:
    mov bx, [si]    // BX - start char code
    cmp bx, 0xFFFF
    je .not_found
    add si, 4

    cmp dx, [si]     // end char code?
    jae .loop        // if searched >= end, load next value
                        // ... if searched < end
    cmp dx, bx       // start char code?
    jb .not_found    // if searched < begin, it's not here

    sub dx, bx       // DX = ((character code - start char code) * 3) + offset
    shl dx, 3
    add dx, [si - 2] // + offset
    cmp dx, [si + 2] // compare to next offset
    jae .not_found   // address out of range

    mov cx, cs
    pop si
    add si, dx       // SI = char data start + DX

text_sjis_default_font_handler_finish:
    pop ds
    pop dx
    pop bx
    ret

.not_found:
    pop si
    stc
    jmp text_sjis_default_font_handler_finish
#endif

    .global __wwcl_font_ank
__wwcl_font_ank:
    .incbin "build/font_ank.dat"

#ifndef __IA16_CMODEL_TINY__
    // TODO: even if a program doesn't use the SJIS font, this pulls in
    // ~55KB of data...
    .global __wwcl_font_sjis
__wwcl_font_sjis:
    .incbin "build/font_sjis.dat"
#endif
