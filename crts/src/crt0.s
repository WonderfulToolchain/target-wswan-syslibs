/**
 * Copyright (c) 2022, 2023 Adrian "asie" Siekierka
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

	.arch	i186
	.code16
	.intel_syntax noprefix

	.section .start, "ax"
	.global _start
_start:
	cli

#ifdef SRAM
	mov	ax, 0x1000
	mov	es, ax
#endif
	// set DS:SI to the location of the data block
	.reloc	.+1, R_386_SEG16, "__wf_data_block!"
	mov	ax, 0
	mov	ds, ax
	mov	si, offset "__wf_data_block"

	// configure SP, ES, SS, flags
	mov	sp, offset "__wf_heap_top"
	xor	ax, ax
#ifndef SRAM
	mov	es, ax
#endif
	mov	ss, ax
	cld

_start_parse_data_block:
	lodsw
	mov	cx, ax
	test	cx, cx
	jz	_start_finish_data_block
	lodsw
	mov	di, ax
	lodsw
#ifndef SRAM
	cmp	di, 0x4000
	jb	_start_parse_data_block_non_wsc

	// data block requests WSC mode?
	in	al, 0xA0
	test	al, 0x02
	// if the console is not color, skip the block entirely
	jz	_start_parse_data_block
	// initialize WSC mode
	in	al, 0x60
	or	al, 0x80
	out	0x60, al
	
_start_parse_data_block_non_wsc:
#endif
	test	ah, 0x80
	jnz	_start_data_block_clear

_start_data_block_move:
	shr	cx, 1
	rep	movsw
	jnc	_start_parse_data_block
	movsb
	jmp	_start_parse_data_block

_start_data_block_clear:
	xor	ax, ax
	shr	cx, 1
	rep	stosw
	jnc	_start_parse_data_block
	stosb
	jmp	_start_parse_data_block

_start_finish_data_block:

	// clear int enable
	out	0xB2, al

	// configure default interrupt base
	mov	al, 0x08
	out	0xB0, al

	// reset console mode to mono
	in	al, 0x60
	and	al, 0x1F
	out	0x60, al

	// initialize DS
	push	es
	pop	ds

	// run constructors
	.reloc	.+1, R_386_SEG16, "__init_array_start!"
	mov ax, 0
	mov es, ax
	mov si, offset __init_array_start
	mov di, offset __init_array_end
	call _start_run_array

#ifdef __IA16_CMODEL_IS_FAR_TEXT
	.reloc	.+3, R_386_SEG16, "main!"
	jmp 0:main
#else
	jmp main
#endif

_start_run_array:
1:
	cmp si, di
	jae 9f
#ifdef __IA16_CMODEL_IS_FAR_TEXT
	es lcall [si]
	add si, 4
#else
	es call [si]
	inc si
	inc si
#endif
	jmp 1b
9:
	ret

	.section .fartext.exit, "ax"
	.global _exit
_exit:
	// run destructors
	.reloc	.+1, R_386_SEG16, "__fini_array_start!"
	mov ax, 0
	mov es, ax
	mov si, offset __fini_array_start
	mov di, offset __fini_array_end
	call _start_run_array

1:
	jmp 1b
