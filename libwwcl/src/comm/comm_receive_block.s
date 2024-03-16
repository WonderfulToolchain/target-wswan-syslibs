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

    .global comm_receive_block
comm_receive_block:
    push bp
    mov bp, sp
	push es
	push di
    push ax
    mov es, dx
	mov di, ax

comm_receive_block_loop:
    push cx
	WF_PLATFORM_CALL comm_receive_char
    pop cx
	test ah, 0x80 // error?
	jnz comm_receive_block_done

	stosb
	loop comm_receive_block_loop

comm_receive_block_done:
    // Save received length
    pop dx
	sub di, dx
    mov [bp + WF_PLATFORM_CALL_STACK_OFFSET(2)], di

	pop di
	pop es
    pop bp
	WF_PLATFORM_RET
