/*
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

/** \file serial.h
	* Functionality related to the serial port.
 */

#if !(defined(LIBWS_API_COMPAT) && LIBWS_API_COMPAT < 202505L)
# error This file should no longer be included directly. Use <ws/uart.h> going forward.
#endif

#ifndef __WF_LIBWS_SERIAL_H__
#define __WF_LIBWS_SERIAL_H__

#include "uart.h"

#define ws_serial_open ws_uart_open
#define ws_serial_close ws_uart_close
#define ws_serial_is_overrun ws_uart_is_rx_overrun
#define ws_serial_ack_overrun ws_uart_ack_rx_overrun
#define ws_serial_is_readable ws_uart_is_rx_ready
#define ws_serial_is_writable ws_uart_is_tx_ready
#define ws_serial_getc ws_uart_getc
#define ws_serial_getc_nonblock ws_uart_getc_nonblock
#define ws_serial_putc ws_uart_putc

/**@}*/

#endif /* __WF_LIBWS_SERIAL_H__ */
