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

	.global ws_portcpy
ws_portcpy:
	push	si
	push	ds
	mov	bx, sp

	mov si, dx
	mov ds, cx
	mov dx, ax
	ss mov	cx, [bx + IA16_CALL_STACK_OFFSET(4)]
	shr	cx, 1
	cld
	jz ws_portcpy_words_end
ws_portcpy_words:
	outsw
	add dx, 2
	loop ws_portcpy_words
ws_portcpy_words_end:
	jnc ws_portcpy_bytes_end
	outsb
ws_portcpy_bytes_end:

	pop	ds
	pop	si
	IA16_RET 0x2
