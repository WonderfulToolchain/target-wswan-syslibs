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

	.global ws_screen_fill_tiles
ws_screen_fill_tiles:
	// AX - destination
	// DX - fill value
	// CX - X
	// stack - Y, width, height

	push	es
	push	di
	push	bp
	mov	bp, sp

#ifdef __IA16_CMODEL_IS_FAR_TEXT
# define STACK_OFFSET 10
#else
# define STACK_OFFSET 8
#endif

	mov	di, ax
	xor	ax, ax
	mov	es, ax

	// AX = Y, CX = X
	// => DI = destination
	mov	ax, [bp + (STACK_OFFSET)]
	and	ax, 0x1F
	shl	ax, 5
	and	cx, 0x1F
	or	ax, cx
	shl	ax, 1
	add	di, ax

	// CX = width, DX = height, AX = fill value
	mov	ax, dx
	mov	cx, [bp + (STACK_OFFSET + 2)]
	and	cx, 0x1F
	jz	__ws_screen_fill_tiles_done
	mov	dx, [bp + (STACK_OFFSET + 4)]
	and	dx, 0x1F
	jz	__ws_screen_fill_tiles_done

	cld
__ws_screen_fill_tiles_row:
	push	cx
	push	di
	rep	stosw
	pop	di
	pop	cx
	add	di, 32 * 2
	dec	dx
	jnz	__ws_screen_fill_tiles_row

__ws_screen_fill_tiles_done:
	pop	bp
	pop	di
	pop	es
	ASM_PLATFORM_RET 0x6
