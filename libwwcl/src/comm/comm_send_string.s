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

    .global comm_send_string
comm_send_string:
    push es
	push si
    mov es, dx 
	mov si, ax

comm_send_string_loop:
	mov bl, es:[si]
	cmp bl, 0
	je comm_send_string_done

	IA16_CALL __wwcl_comm_send_char_inner
	test ah, 0x80 // error?
	jnz comm_send_string_done

	inc si
	jmp comm_send_string_loop

comm_send_string_done:
	pop si
    pop es
	IA16_RET
