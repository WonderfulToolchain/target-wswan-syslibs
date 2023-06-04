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

	.global ws_screen_put_tiles
ws_screen_put_tiles:
	// AX - destination
	// CX:DX - source
	// stack - X, Y, width, height

	push	ds
	push	es
	push	si
	push	di
	push	bp
	mov	bp, sp

#ifdef __IA16_CMODEL_IS_FAR_TEXT
# define STACK_OFFSET 14
#else
# define STACK_OFFSET 12
#endif

	// adjust values:
	// DS:SI - source
	// ES:?? - destination
	mov	di, ax
	xor	ax, ax
	mov	es, ax
	mov	si, dx
	mov	ds, cx

	// AX = Y, BX = X
	// => DI = destination
	mov	ax, [bp + (STACK_OFFSET + 2)]
	and	ax, 0x1F
	shl	ax, 5
	mov	bx, [bp + (STACK_OFFSET)]
	and	bx, 0x1F
	or	ax, bx
	shl	ax, 1
	add	di, ax

	// CX = width, AX = height
	mov	cx, [bp + (STACK_OFFSET + 4)]
	and	cx, 0x1F
	jz	__ws_screen_put_tiles_done
	mov	ax, [bp + (STACK_OFFSET + 6)]
	and	ax, 0x1F
	jz	__ws_screen_put_tiles_done

	cld
__ws_screen_put_tiles_row:
	push	cx
	push	di
	rep	movsw
	pop	di
	pop	cx
	add	di, 32 * 2
	dec	ax
	jnz	__ws_screen_put_tiles_row

__ws_screen_put_tiles_done:
	pop	bp
	pop	di
	pop	si
	pop	es
	pop	ds
	ASM_PLATFORM_RET 0x8
