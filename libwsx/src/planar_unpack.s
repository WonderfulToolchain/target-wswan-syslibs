/**
 * Copyright (c) 2023 Adrian "asie" Siekierka
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
#include "asm-preamble.h"
	.intel_syntax noprefix

// Calling convention for planar_unpack methods:
// DS:SI - source
// ES:DI - destination
// CX - length
// AL - mode

__wsx_planar_unpack_word_table:
	.word 0x0000, 0x00FF, 0xFF00, 0xFFFF

__wsx_planar_unpack_1to2_zero:
	mov bx, ax
	shl bx, 1
	mov bx, cs:[__wsx_planar_unpack_word_table + bx]
#ifdef __IA16_TUNE_NEC_V30MZ
	.align 2, 0x90
#endif
__wsx_planar_unpack_1to2_zero_loop:
	lodsb
	mov ah, al
	and ax, bx
	stosw
	loop __wsx_planar_unpack_1to2_zero_loop
	ret

__wsx_planar_unpack_1to4_zero:
	mov bx, ax
	shr bx, 1
	and bx, 6
	mov dx, cs:[__wsx_planar_unpack_word_table + bx]
	mov bx, ax
	shl bx, 1
	and bx, 6
	mov bx, cs:[__wsx_planar_unpack_word_table + bx]
#ifdef __IA16_TUNE_NEC_V30MZ
	.align 2, 0x90
#endif
__wsx_planar_unpack_1to4_zero_loop:
	lodsb
	mov ah, al
	push ax
	and ax, bx
	stosw
	pop ax
	and ax, dx
	stosw
	loop __wsx_planar_unpack_1to4_zero_loop
	ret

__wsx_planar_unpack_1to2:
	// BX, DX free
	// BX = background mask
	// DX = foreground mask

	// to convert 0,1 (a) to 0,FF (A):
	// A = (a^1)-1
	// TODO: this might be faster, smaller, better as a table

	not al

	mov dl, al
	and dl, 1
	dec dl
	shr al, 1

	mov dh, al
	and dh, 1
	dec dh
	shr al, 1

	mov bl, al
	and bl, 1
	dec bl
	shr al, 1

	mov bh, al
	and bh, 1
	dec bh

#ifdef __IA16_TUNE_NEC_V30MZ
	.align 2, 0x90
#endif
__wsx_planar_unpack_1to2_loop:
	lodsb
	mov ah, al
	push dx
	and dx, ax
	not ax
	and ax, bx
	or ax, dx
	pop dx
	stosw
	loop __wsx_planar_unpack_1to2_loop
	ret

__wsx_planar_unpack_mode_table:
	.word __wsx_planar_unpack_1to2_zero
	.word __wsx_planar_unpack_1to4_zero
	.word __wsx_planar_unpack_1to2

	.global wsx_planar_unpack
wsx_planar_unpack:
	// DX:AX = destination pointer
	// CX = length
	// stack(4) = source pointer
	// stack(1) = offset (=> BL)
	// stack(1) = mode (=> BH)

	push si
	push di
	push ds
	push es
	push bp
	mov bp, sp

	// move destination pointer to ES:DI, source pointer to DS:SI
	// load offset+flags in BX
	mov es, dx
	mov di, ax
#ifdef __IA16_CMODEL_IS_FAR_TEXT
	lds si, [bp + 14]
	mov bx, [bp + 18]
#else
	lds si, [bp + 12]
	mov bx, [bp + 16]
#endif

	mov ax, bx
	shr bx, 7
	and bx, 0x00FE
	cld
	call cs:[__wsx_planar_unpack_mode_table + bx]
		
	pop bp
	pop es
	pop ds
	pop di
	pop si
	ASM_PLATFORM_RET
