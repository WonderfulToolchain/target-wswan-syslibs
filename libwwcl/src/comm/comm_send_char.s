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

#define ERR_SIO_BUSY      0x8100
#define ERR_SIO_TIMEOUT   0x8101
#define ERR_SIO_OVERRUN   0x8102
#define ERR_SIO_CANCEL    0x8103

    .global comm_send_char
comm_send_char:
    mov bl, al // BL = char

	.global __wwcl_comm_send_char_inner
__wwcl_comm_send_char_inner:
	in al, IO_HWINT_ENABLE
	push ax
	mov cx, [__wwcl_comm_tx_timeout]

	in al, IO_SERIAL_STATUS
	test al, SERIAL_TX_READY
	je comm_send_char_send
	cmp cx, 0x0000 // instant timeout?
	je comm_send_char_timeout

	// Enable listening on serial TX
	mov al, HWINT_VBLANK | HWINT_SERIAL_TX
	out IO_HWINT_ENABLE, al

comm_send_char_loop:
	hlt
	nop

	in al, IO_SERIAL_STATUS
	test al, SERIAL_TX_READY
	je comm_send_char_send

	// if we're here, the IRQ received was VBLANK
    push cx
    IA16_CALL key_press_check
    pop cx
	and ax, [__wwcl_comm_cancel_key]
	cmp ax, [__wwcl_comm_cancel_key] 
	je comm_send_char_cancel

	cmp cx, 0xFFFF // no timeout?
	je comm_send_char_loop
	loop comm_send_char_loop

comm_send_char_timeout:
	// Timeout
	pop ax
	out IO_HWINT_ENABLE, al
	mov ax, ERR_SIO_TIMEOUT
	IA16_RET

comm_send_char_cancel:
	// Cancel
	pop ax
	out IO_HWINT_ENABLE, al
	mov ax, ERR_SIO_CANCEL
	IA16_RET

comm_send_char_send:
	mov al, bl
	out IO_SERIAL_DATA, al

	pop ax
	out IO_HWINT_ENABLE, al
	xor ax, ax
	IA16_RET
