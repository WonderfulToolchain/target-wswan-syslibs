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

/** \file cart/rtc.h
	* Functionality related to the cartridge RTC.
 */

#ifndef LIBWS_CART_RTC_H_
#define LIBWS_CART_RTC_H_

#include "../ports.h"

/**
 * @addtogroup cart_rtc Cartridge - RTC
 * @{
 */

#define WS_CART_RTC_MONTH_AMPM 0x80
#define WS_CART_RTC_MONTH_AM   0x00
#define WS_CART_RTC_MONTH_PM   0x80

#define WS_CART_RTC_STATUS_POWER_LOST 0x80
#define WS_CART_RTC_STATUS_12_HOUR    0x00
#define WS_CART_RTC_STATUS_24_HOUR    0x40
#define WS_CART_RTC_STATUS_INTAE      0x20
#define WS_CART_RTC_STATUS_INTME      0x08
#define WS_CART_RTC_STATUS_INTFE      0x02
#define WS_CART_RTC_STATUS_INT_OFF    0
#define WS_CART_RTC_STATUS_INT_FREQ_STEADY (WS_CART_RTC_STATUS_INTFE)
#define WS_CART_RTC_STATUS_INT_MINUTE_EDGE (WS_CART_RTC_STATUS_INTME)
#define WS_CART_RTC_STATUS_INT_MINUTE_STEADY (WS_CART_RTC_STATUS_INTME | WS_CART_RTC_STATUS_INTFE)
#define WS_CART_RTC_STATUS_INT_ALARM (WS_CART_RTC_STATUS_INTAE)

#ifndef __ASSEMBLER__

#include <stdbool.h>
#include <stdint.h>
#include <wonderful.h>

/**
 * @brief Structure containing the date read from the RTC, BCD-encoded.
 */
typedef struct __attribute__((packed)) {
    uint8_t year;
    uint8_t month;
    uint8_t date;
    uint8_t day;
} ws_cart_rtc_date_t;

/**
 * @brief Structure containing the time read from the RTC, BCD-encoded.
 */
typedef struct __attribute__((packed)) {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} ws_cart_rtc_time_t;

typedef struct __attribute__((packed)) {
    ws_cart_rtc_date_t date;
    ws_cart_rtc_time_t time;
} ws_cart_rtc_datetime_t;

/**
 * @brief Wait until the RTC is ready.
 */
bool ws_cart_rtc_wait_ready(void);

/**
 * @brief Send command and read from RTC.
 *
 * Upon buffer overflow, any additional bytes read are ignored, but the transaction is completed.
 * 
 * @param command Command
 * @param buffer Buffer to write to
 * @param length Length of buffer
 * @return uint16_t Number of bytes read (can be smaller than, equal, or larger than buffer)
 */
uint16_t ws_cart_rtc_read(uint8_t command, void __wf_cram* buffer, uint16_t length);

/**
 * @brief Send command and write to RTC.
 *
 * Upon buffer overflow, the byte 0x00 is sent for all remaining bytes.
 * 
 * @param command Command
 * @param buffer Buffer to read from
 * @param length Length of buffer
 * @return uint16_t Number of bytes written (can be smaller than, equal, or larger than buffer)
 */
uint16_t ws_cart_rtc_write(uint8_t command, const void __wf_cram* buffer, uint16_t length);

static inline bool ws_cart_rtc_reset(void) {
    if (!ws_cart_rtc_wait_ready()) return false;
    outportb(WS_CART_RTC_CTRL_PORT, WS_CART_RTC_CTRL_CMD_RESET | WS_CART_RTC_CTRL_ACTIVE);
}

static inline bool ws_cart_rtc_read_status(uint8_t __wf_cram* result) {
    return ws_cart_rtc_read(WS_CART_RTC_CTRL_CMD_READ_STATUS, result, 1) == 1;
}

static inline bool ws_cart_rtc_write_status(uint8_t result) {
    return ws_cart_rtc_write(WS_CART_RTC_CTRL_CMD_WRITE_STATUS, &result, 1) == 1;
}

static inline bool ws_cart_rtc_read_datetime(ws_cart_rtc_datetime_t __wf_cram* result) {
    return ws_cart_rtc_read(WS_CART_RTC_CTRL_CMD_READ_DATETIME, result, sizeof(ws_cart_rtc_datetime_t)) == sizeof(ws_cart_rtc_datetime_t);
}

static inline bool ws_cart_rtc_write_datetime(ws_cart_rtc_datetime_t __wf_cram* result) {
    return ws_cart_rtc_write(WS_CART_RTC_CTRL_CMD_WRITE_DATETIME, result, sizeof(ws_cart_rtc_datetime_t)) == sizeof(ws_cart_rtc_datetime_t);
}

static inline bool ws_cart_rtc_read_time(ws_cart_rtc_time_t __wf_cram* result) {
    return ws_cart_rtc_read(WS_CART_RTC_CTRL_CMD_READ_TIME, result, sizeof(ws_cart_rtc_time_t)) == sizeof(ws_cart_rtc_time_t);
}

static inline bool ws_cart_rtc_write_time(ws_cart_rtc_time_t __wf_cram* result) {
    return ws_cart_rtc_write(WS_CART_RTC_CTRL_CMD_WRITE_TIME, result, sizeof(ws_cart_rtc_time_t)) == sizeof(ws_cart_rtc_time_t);
}

static inline bool ws_cart_rtc_write_alarm(uint16_t alarm) {
    alarm = __builtin_bswap16(alarm);
    return ws_cart_rtc_write(WS_CART_RTC_CTRL_CMD_WRITE_ALARM, &alarm, 2) == 2;
}

/**@}*/

#endif /* __ASSEMBLER__ */

#endif /* LIBWS_CART_RTC_H_ */
