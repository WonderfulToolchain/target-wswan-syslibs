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

	.global ws_screen_modify_tiles
ws_screen_modify_tiles:
	// AX - destination
	// DX - mask
	// CX - value
	// stack - X, Y, width, height

	push	ds
	push	es
	push	si
	push	di
	push	bp
	mov	bp, sp

	// adjust values:
	// ES:?? - destination
	mov	di, ax
	mov	ax, ss
	mov	ds, ax
	mov	es, ax

	// AX = Y, BX = X
	// => DI = destination
	mov	ax, [bp + WF_PLATFORM_CALL_STACK_OFFSET(12)]
	and	ax, 0x1F
	shl	ax, 5
	mov	bx, [bp + WF_PLATFORM_CALL_STACK_OFFSET(10)]
	and	bx, 0x1F
	or	ax, bx
	shl	ax, 1
	add	di, ax

	mov	bx, cx
	// CX = width, BP = height
	mov	cx, [bp + WF_PLATFORM_CALL_STACK_OFFSET(14)]
	test	cx, cx
	jz	__ws_screen_modify_tiles_done
	mov	ax, [bp + WF_PLATFORM_CALL_STACK_OFFSET(16)]
	test	ax, ax
	jz	__ws_screen_modify_tiles_done
	mov	bp, ax

	cld
__ws_screen_modify_tiles_row:
	mov	si, di
	push	cx
	push	di
__ws_screen_modify_tiles_loop:
	lodsw
	and	ax, dx
	or	ax, bx
	stosw
	loop	__ws_screen_modify_tiles_loop

	pop	di
	pop	cx

	add	di, 32 * 2
	dec	bp
	jnz	__ws_screen_modify_tiles_row

__ws_screen_modify_tiles_done:
	pop	bp
	pop	di
	pop	si
	pop	es
	pop	ds
	ASM_PLATFORM_RET 0x8
