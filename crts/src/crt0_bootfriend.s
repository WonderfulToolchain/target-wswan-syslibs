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

_header:
	.byte	0x62, 0x46 /* BootFriend magic */
	.word	offset "_start" /* program counter value */

_start:
	cli

	xor	ax, ax
	// CS = 0x0000
	mov	ds, ax
	mov	es, ax
	mov	ss, ax

	// configure SP
	mov	sp, 0xFE00

	// clear int enable
	out	0xB2, al

	// clear BSS
	mov	di, offset "__edata"
	mov	cx, offset "__lwbss"
	cld
	rep	stosw

	// configure default interrupt base
	mov	al, 0x08
	out	0xB0, al

	jmp	main
