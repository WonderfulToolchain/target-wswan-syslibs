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

	.global __libws_screen_put_tiles
__libws_screen_put_tiles:
	// AX - destination
	// CX:DX - source
	// stack - X, Y, width, height

	push	ds
	push	es
	push	si
	push	di
	push	bp
	mov	bp, sp

	// adjust values:
	// DS:SI - source
	// ES:?? - destination
	mov	di, ax
	push	ss
	pop	es
	mov	si, dx
	mov	ds, cx

	// AX = Y, BX = X
	// => DI = destination
	mov	ax, [bp + IA16_CALL_STACK_OFFSET(12)]
	and	ax, 0x1F
	shl	ax, 5
	mov	bx, [bp + IA16_CALL_STACK_OFFSET(10)]
	and	bx, 0x1F
	or	ax, bx
	shl	ax, 1
	add	di, ax

	// CX = width, AX = height, DX = pitch
	mov	cx, [bp + IA16_CALL_STACK_OFFSET(14)]
	test	cx, cx
	jz	__ws_screen_put_tiles_done
	mov	ax, [bp + IA16_CALL_STACK_OFFSET(16)]
	test	ax, ax
	jz	__ws_screen_put_tiles_done
	mov	dx, [bp + IA16_CALL_STACK_OFFSET(18)]
	test	dx, dx
	jz	__ws_screen_put_tiles_done

	mov	bx, 32
	sub	bx, cx
	shl	bx, 1
	sub	dx, cx
	shl	dx, 1

	cld
	.balign 2, 0x90
__ws_screen_put_tiles_row:
	push	cx
	rep	movsw
	pop	cx
	add	si, dx
	add	di, bx
	dec	ax
	jnz	__ws_screen_put_tiles_row

__ws_screen_put_tiles_done:
	pop	bp
	pop	di
	pop	si
	pop	es
	pop	ds
	IA16_RET 10
