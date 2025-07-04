/**
 * Copyright (c) 2022 Adrian "asie" Siekierka
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
#include "ws/ports.h"
#include "asm-preamble.h"
	.intel_syntax noprefix

	.global ws_keypad_scan
ws_keypad_scan:
	mov	dx, WS_KEY_SCAN_PORT

	mov	al, 0x10
	out	dx, al
	daa
	in	al, dx
	and	al, 0x0F
	mov	ch, al

	mov	al, 0x20
	out	dx, al
	daa
	in	al, dx
	shl	al, 4
	mov	cl, al

	mov	al, 0x40
	out	dx, al
	daa
	in	al, dx
	and	al, 0x0F
	or	cl, al

	mov	ax, cx
	IA16_RET
