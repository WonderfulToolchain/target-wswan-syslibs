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
#include "ws/ports.h"
#include "asm-preamble.h"
	.intel_syntax noprefix

	.global ws_uart_getc
ws_uart_getc:
    in al, WS_UART_CTRL_PORT
    test al, WS_UART_CTRL_RX_OVERRUN
    jz ws_uart_getc_no_overrun
    or al, WS_UART_CTRL_RX_OVERRUN_RESET
    out WS_UART_CTRL_PORT, al
ws_uart_getc_no_overrun:
    test al, WS_UART_CTRL_RX_READY
    jz ws_uart_getc
    in al, WS_UART_DATA_PORT
    IA16_RET
