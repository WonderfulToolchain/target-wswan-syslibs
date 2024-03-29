/**
 * Copyright (c) 2022, 2023 Adrian "asie" Siekierka
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
#include "ws/hardware.h"
#include "asm-preamble.h"
	.intel_syntax noprefix

	.global ws_serial_putc
ws_serial_putc:
    mov ah, al
ws_serial_putc_ready_loop:
    in al, IO_SERIAL_STATUS
    test al, SERIAL_TX_READY
    jz ws_serial_putc_ready_loop
    mov al, ah
    out IO_SERIAL_DATA, al
    ASM_PLATFORM_RET
