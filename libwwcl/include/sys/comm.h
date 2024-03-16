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

/** \file sys/comm.h
 * FreyaBIOS serial calls.
 */

#ifndef __WF_LIBWW_COMM_H__
#define __WF_LIBWW_COMM_H__

#include <ws.h>
#include "types.h"

/**
 * @addtogroup Int14 BIOS - INT 14h - Serial
 * @{
 */

#define ERR_SIO_BUSY      0x8100
#define ERR_SIO_TIMEOUT   0x8101
#define ERR_SIO_OVERRUN   0x8102
#define ERR_SIO_CANCEL    0x8103

void comm_open(void);
void comm_close(void);
uint16_t comm_send_char(int c);
int comm_receive_char(void);
int comm_receive_with_timeout(uint16_t timeout);
uint16_t comm_send_string(const char __far* str);
uint16_t comm_send_block(const void __far* buf, uint16_t length);
void comm_receive_block(const void __far* buf, uint16_t length, uint16_t *out_length);
void comm_set_timeout(uint16_t recv_timeout, uint16_t send_timeout);

#define COMM_SPEED_9600 0
#define COMM_SPEED_38400 1

/**
 * @brief Set the new baud rate.
 *
 * This function cannot be called while the serial connection is open.
 * 
 * @param rate The new baud rate ( @ref COMM_SPEED_9600 or @ref COMM_SPEED_38400 )
 */
void comm_set_baudrate(uint16_t rate);
uint16_t comm_get_baudrate(void);

void comm_set_cancel_key(uint16_t value);
uint16_t comm_get_cancel_key(void);

// Missing: comm_xmodem

/**@}*/

#endif /* __WF_LIBWW_COMM_H__ */
