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

    .global comm_receive_char
comm_receive_char:
	mov cx, [__wwcl_comm_rx_timeout]
    jmp comm_receive_char_with_timeout_inner

    .global comm_receive_char_with_timeout
comm_receive_char_with_timeout:
    mov cx, ax
comm_receive_char_with_timeout_inner:
	in al, IO_HWINT_ENABLE
	push ax

	// Do an early receive (for performance)
	in al, IO_SERIAL_STATUS
	test al, (SERIAL_OVERRUN | SERIAL_RX_READY)
	je comm_recieve_char_received
	test cx, cx // instant timeout?
	jz comm_recieve_char_timeout

	// Enable listening on serial RX
	mov al, HWINT_VBLANK | HWINT_SERIAL_RX
	out IO_HWINT_ENABLE, al

comm_recieve_char_loop:
	hlt
	nop

	in al, IO_SERIAL_STATUS
	test al, (SERIAL_OVERRUN | SERIAL_RX_READY)
	je comm_recieve_char_received

	// if we're here, the IRQ received was VBLANK
    push cx
	WF_PLATFORM_CALL key_press_check
    pop cx
	and ax, [__wwcl_comm_cancel_key]
	cmp ax, [__wwcl_comm_cancel_key] 
	je comm_recieve_char_cancel

	cmp cx, 0xFFFF // no timeout?
	je comm_recieve_char_loop
	loop comm_recieve_char_loop	

comm_recieve_char_timeout:
	// Timeout
	pop ax
	out IO_HWINT_ENABLE, al
	mov ax, ERR_SIO_TIMEOUT
	WF_PLATFORM_RET

comm_recieve_char_cancel:
	// Cancel
	pop ax
	out IO_HWINT_ENABLE, al
	mov ax, ERR_SIO_CANCEL
	WF_PLATFORM_RET

comm_recieve_char_received:
	in al, IO_SERIAL_DATA
	mov ah, al

	// Overrun could have happened between the first port read and now
	// If it didn't happen, we know SERIAL_RX_READY was the set bit
	in al, IO_SERIAL_STATUS
	test al, SERIAL_OVERRUN
	jnz comm_recieve_char_overrun

	// Success
	pop ax
	out IO_HWINT_ENABLE, al
	mov al, ah
	xor ah, ah
	WF_PLATFORM_RET

comm_recieve_char_overrun:
	or al, SERIAL_OVERRUN_RESET
	out IO_SERIAL_STATUS, al

	pop ax
	out IO_HWINT_ENABLE, al
	mov ax, ERR_SIO_OVERRUN
	WF_PLATFORM_RET
