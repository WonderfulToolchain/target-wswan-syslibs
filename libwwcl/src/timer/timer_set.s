/**
 * Copyright (c) 2023, 2024 Adrian "asie" Siekierka
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
#include <ws.h>
#include "asm-preamble.h"
	.intel_syntax noprefix

__wwcl_timer_set:
	// AL = timer type (0 = HBlank, 1 = VBlank)
	// BX = timer value (0 = disabled, 1 = enabled, 3 = autopreset)
	mov cl, al
	shl cl, 1 // shift: 0 = HBlank, 2 = VBlank

	mov al, 0xFC
	rol al, cl // create mask
	shl bl, cl // create OR value
	mov cl, al

	in al, IO_TIMER_CTRL
	and al, cl
	or al, bl
	out IO_TIMER_CTRL, al

	WF_PLATFORM_RET

	.global timer_enable
timer_enable:
	push ax
	push ax

	// disable timer
	xor bx, bx
	WF_PLATFORM_CALL __wwcl_timer_set

	// set reload preset
	pop ax
	shl al, 1
	xor dh, dh
	mov dl, al
	add dl, 0xA4

	mov ax, cx
	out dx, ax

	// enable timer
	pop bx
	and bx, 1
	shl bx, 1
	or bl, 1
	
	jmp __wwcl_timer_set

	.global timer_disable
timer_disable:
	xor bx, bx
	jmp __wwcl_timer_set
