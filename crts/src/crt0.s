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

	// set DS:SI to the location of the data block
	.reloc	.+1, R_386_SEG16, "__wf_data_block!"
	mov	ax, 0
	mov	ds, ax
	mov	si, offset "__wf_data_block"

	// configure SP, ES, SS, flags
	mov	sp, offset "__wf_heap_top"
	xor	ax, ax
	mov	es, ax
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

	// initialize DS
	xor	ax, ax
	mov	ds, ax

	// clear int enable
	out	0xB2, al

	// configure default interrupt base
	mov	al, 0x08
	out	0xB0, al

#ifdef __IA16_CMODEL_IS_FAR_TEXT
	.reloc	.+3, R_386_SEG16, "main!"
	jmp 0:main
#else
	jmp main
#endif
