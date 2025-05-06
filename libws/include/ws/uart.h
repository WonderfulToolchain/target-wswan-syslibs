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

/** \file uart.h
 * Functionality related to the UART EXT port.
 */

#ifndef LIBWS_UART_H_
#define LIBWS_UART_H_

#include <stdbool.h>
#include <stdint.h>
#include "ports.h"
#include "util.h"

/**
 * @addtogroup uart UART (EXT port)
 * @{
 */

static inline void ws_uart_open(uint8_t baud_rate) {
	outportb(WS_UART_CTRL_PORT, WS_UART_CTRL_ENABLE | WS_UART_CTRL_RX_OVERRUN_RESET | baud_rate);
}

static inline void ws_uart_close(void) {
	outportb(WS_UART_CTRL_PORT, 0x00);
}

static inline bool ws_uart_is_rx_overrun(void) {
	return inportb(WS_UART_CTRL_PORT) & WS_UART_CTRL_RX_OVERRUN;
}

static inline void ws_uart_ack_rx_overrun(void) {
	outportb(WS_UART_CTRL_PORT, inportb(WS_UART_CTRL_PORT) | WS_UART_CTRL_RX_OVERRUN_RESET);
}

static inline bool ws_uart_is_rx_ready(void) {
	return inportb(WS_UART_CTRL_PORT) & WS_UART_CTRL_RX_READY;
}

static inline bool ws_uart_is_tx_ready(void) {
	return inportb(WS_UART_CTRL_PORT) & WS_UART_CTRL_TX_READY;
}

uint8_t ws_uart_getc(void);
int16_t ws_uart_getc_nonblock(void);
void ws_uart_putc(uint8_t value);

/**@}*/

#endif /* LIBWS_UART_H_ */
