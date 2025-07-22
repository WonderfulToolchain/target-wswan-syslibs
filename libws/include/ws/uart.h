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

 /**
  * @brief UART baud rate.
  */
typedef enum {
	WS_UART_BAUD_RATE_9600 = WS_UART_CTRL_BAUD_9600, ///< UART baud rate: 9600 baud (960 bytes/second).
	WS_UART_BAUD_RATE_38400 = WS_UART_CTRL_BAUD_38400 ///< UART baud rate: 38400 baud (3840 bytes/second).
} ws_uart_baud_rate_t;

/**
 * @brief Open the UART (EXT port) connection.
 * 
 * @param baud_rate The baud rate to use for the connection.
 * @see WS_UART_BAUD_RATE_9600
 * @see WS_UART_BAUD_RATE_38400
 */
static inline void ws_uart_open(uint8_t baud_rate) {
	outportb(WS_UART_CTRL_PORT, WS_UART_CTRL_ENABLE | WS_UART_CTRL_RX_OVERRUN_RESET | baud_rate);
}

/**
 * @brief Close the UART (EXT port) connection.
 */
static inline void ws_uart_close(void) {
	outportb(WS_UART_CTRL_PORT, 0x00);
}

/**
 * @brief Check if the UART receive buffer has overflowed.
 */
static inline bool ws_uart_is_rx_overrun(void) {
	return inportb(WS_UART_CTRL_PORT) & WS_UART_CTRL_RX_OVERRUN;
}

/**
 * @brief Acknowledge that the UART receive buffer has overflowed.
 *
 * This is meant to be used after you have recovered from the overrun event
 * (for example, by sending a cancellation message). 
 */
static inline void ws_uart_ack_rx_overrun(void) {
	outportb(WS_UART_CTRL_PORT, inportb(WS_UART_CTRL_PORT) | WS_UART_CTRL_RX_OVERRUN_RESET);
}

/**
 * @brief Does the UART receive buffer contain a byte?
 * 
 * @return True if a byte can be read from the receive buffer.
 */
static inline bool ws_uart_is_rx_ready(void) {
	return inportb(WS_UART_CTRL_PORT) & WS_UART_CTRL_RX_READY;
}

/**
 * @brief Is the UART transmit buffer ready to accept a byte?
 * 
 * @return True if a byte can be written to the transmit buffer.
 */
static inline bool ws_uart_is_tx_ready(void) {
	return inportb(WS_UART_CTRL_PORT) & WS_UART_CTRL_TX_READY;
}

/**
 * @brief Read a character from the UART.
 *
 * This function blocks until a character is successfully read.
 * 
 * @return uint8_t The character read.
 */
uint8_t ws_uart_getc(void);

/**
 * @brief Try to read a character from the UART.
 * 
 * @return int16_t The character read (>= 0) or a negative value if no
 * character has been read.
 */
int16_t ws_uart_getc_nonblock(void);

/**
 * @brief Write a character to the UART.
 *
 * This ufnction blocks until a character is successfully written.
 * 
 * @param value The character to write.
 */
void ws_uart_putc(uint8_t value);

/**@}*/

#endif /* LIBWS_UART_H_ */
