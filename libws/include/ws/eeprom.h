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

/** \file eeprom.h
	* Functionality related to EEPROM.
 */

#ifndef LIBWS_EEPROM_H_
#define LIBWS_EEPROM_H_

#define WS_IEEP_SIZE_MONO  0x80
#define WS_IEEP_SIZE_COLOR 0x800

#define WS_IEEP_USER_ADDR 0x00
#define WS_IEEP_USER_SIZE 0x60

#define WS_IEEP_OWNER_NAME_ADDR           0x60 /* 16 bytes */
#define WS_IEEP_OWNER_NAME_SIZE           16
#define WS_IEEP_OWNER_BIRTHDAY_YEAR_ADDR  0x70 /* word */
#define WS_IEEP_OWNER_BIRTHDAY_MONTH_ADDR 0x72 /* byte */
#define WS_IEEP_OWNER_BIRTHDAY_DAY_ADDR   0x73 /* byte */
#define WS_IEEP_OWNER_GENDER_ADDR         0x74 /* byte */

#ifdef __ASSEMBLER__

#define WS_IEEP_GENDER_UNK    0
#define WS_IEEP_GENDER_MALE   1
#define WS_IEEP_GENDER_FEMALE 2

#else

/**
 * Possible IEEPROM gender values.
 */
enum ws_ieep_gender {
	WS_IEEP_GENDER_UNK    = 0,
	WS_IEEP_GENDER_MALE   = 1,
	WS_IEEP_GENDER_FEMALE = 2
};

#endif

#define WS_IEEP_OWNER_BLOOD_TYPE_ADDR     0x75 /* byte */

#ifdef __ASSEMBLER__

#define WS_IEEP_BLOOD_TYPE_UNK 0
#define WS_IEEP_BLOOD_TYPE_A   1
#define WS_IEEP_BLOOD_TYPE_B   2
#define WS_IEEP_BLOOD_TYPE_0   3
#define WS_IEEP_BLOOD_TYPE_AB  4

#else

/**
 * Possible IEEPROM blood type values.
 */
enum ws_ieep_blood_type {
	WS_IEEP_BLOOD_TYPE_UNK = 0,
	WS_IEEP_BLOOD_TYPE_A   = 1,
	WS_IEEP_BLOOD_TYPE_B   = 2,
	WS_IEEP_BLOOD_TYPE_0   = 3,
	WS_IEEP_BLOOD_TYPE_AB  = 4
};

#endif

#define WS_IEEP_LAST_CART_PUBLISHER_ADDR  0x76 /* byte */
#define WS_IEEP_LAST_CART_PLATFORM_ADDR   0x77 /* byte */
#define WS_IEEP_LAST_CART_GAME_ID_ADDR    0x78 /* byte */
#define WS_IEEP_CART_CHANGE_COUNT_ADDR    0x7C /* byte */
#define WS_IEEP_NAME_CHANGE_COUNT_ADDR    0x7D /* byte */
#define WS_IEEP_STARTUP_COUNT_ADDR        0x7E /* word */

#define WS_IEEP_COLOR_SETTINGS_ADDR       0x83 /* byte */
#define WS_IEEP_COLOR_SETTINGS_CUSTOM_SPLASH     0x80
#define WS_IEEP_COLOR_SETTINGS_WSC_HIGH_CONTRAST 0x40
#define WS_IEEP_COLOR_SETTINGS_VOLUME(x)         ((x) & 3)
#define WS_IEEP_COLOR_SETTINGS_VOLUME_MASK       0x03

#define WS_IEEP_NAME_COLOR_ADDR           0x84 /* byte */

#ifdef __ASSEMBLER__

#define WS_IEEP_NAME_COLOR_BLACK   0x00
#define WS_IEEP_NAME_COLOR_RED     0x01
#define WS_IEEP_NAME_COLOR_ORANGE  0x02
#define WS_IEEP_NAME_COLOR_YELLOW  0x03
#define WS_IEEP_NAME_COLOR_LIME    0x04
#define WS_IEEP_NAME_COLOR_GREEN   0x05
#define WS_IEEP_NAME_COLOR_TEAL    0x06
#define WS_IEEP_NAME_COLOR_CYAN    0x07
#define WS_IEEP_NAME_COLOR_SEABLUE 0x08
#define WS_IEEP_NAME_COLOR_BLUE    0x09
#define WS_IEEP_NAME_COLOR_PURPLE  0x0A
#define WS_IEEP_NAME_COLOR_PINK    0x0B
#define WS_IEEP_NAME_COLOR_FUCHSIA 0x0C
#define WS_IEEP_NAME_COLOR_WHITE   0x0D

#else

/**
 * Possible IEEPROM name color values.
 */
enum ws_ieep_name_color {
	WS_IEEP_NAME_COLOR_BLACK = 0x00, ///< RGB(0, 0, 0)
	WS_IEEP_NAME_COLOR_RED = 0x01, ///< RGB(15, 0, 0)
	WS_IEEP_NAME_COLOR_ORANGE = 0x02, ///< RGB(15, 7, 0)
	WS_IEEP_NAME_COLOR_YELLOW = 0x03, ///< RGB(15, 15, 0)
	WS_IEEP_NAME_COLOR_LIME = 0x04, ///< RGB(7, 15, 0)
	WS_IEEP_NAME_COLOR_GREEN = 0x05, ///< RGB(0, 15, 0)
	WS_IEEP_NAME_COLOR_TEAL = 0x06, ///< RGB(0, 15, 7)
	WS_IEEP_NAME_COLOR_CYAN = 0x07, ///< RGB(0, 15, 15)
	WS_IEEP_NAME_COLOR_SEABLUE = 0x08, ///< RGB(0, 7, 15)
	WS_IEEP_NAME_COLOR_BLUE = 0x09, ///< RGB(0, 0, 15)
	WS_IEEP_NAME_COLOR_PURPLE = 0x0A, ///< RGB(7, 0, 15)
	WS_IEEP_NAME_COLOR_PINK = 0x0B, ///< RGB(15, 0, 15)
	WS_IEEP_NAME_COLOR_FUCHSIA = 0x0C, ///< RGB(15, 0, 7)
	WS_IEEP_NAME_COLOR_WHITE = 0x0D  ///< RGB(15, 15, 15)
};

#endif

#ifndef __ASSEMBLER__

#include <stdbool.h>
#include <stdint.h>
#include "ports.h"
#include "util.h"

/**
 * @addtogroup eeprom EEPROM
 * @{
 */

typedef struct {
	uint8_t port;
	uint8_t dwords; // bits - 2
} ws_eeprom_handle_t;

ws_eeprom_handle_t ws_eeprom_handle_internal(void);

static inline ws_eeprom_handle_t ws_eeprom_handle_cartridge(uint8_t bits) {
	ws_eeprom_handle_t handle = {0xC4, bits - 2};
	return handle;
}

/**
 * @brief Read an aligned word from the EEPROM.
 * 
 * @param address The address to read from. The lowest bit is ignored.
 * @return uint16_t The value read.
 */
uint16_t ws_eeprom_read_word(ws_eeprom_handle_t handle, uint16_t address);

/**
 * @brief Read a byte from the EEPROM.
 * 
 * @param address The address to read from.
 * @return uint8_t The value read.
 */
uint8_t ws_eeprom_read_byte(ws_eeprom_handle_t handle, uint16_t address);

/**
 * @brief Read bytes from the EEPROM.
 * 
 * @param address The address to read from.
 * @param data The pointer to write to.
 * @param length The number of bytes to read.
 */
void ws_eeprom_read_data(ws_eeprom_handle_t handle, uint16_t address, uint8_t *data, uint16_t length);

/**
 * @brief Write a word to the EEPROM.
 * 
 * @param address The address to write to. The lowest bit is ignored.
 * @param value The word to write.
 * @return True if the write was successful (no timeout).
 */
bool ws_eeprom_write_word(ws_eeprom_handle_t handle, uint16_t address, uint16_t value);

/**
 * @brief Erase a word from the EEPROM, setting it to 0xFFFF.
 * 
 * @param address The address to erase.
 * @return True if the erase was successful (no timeout).
 */
bool ws_eeprom_erase_word(ws_eeprom_handle_t handle, uint16_t address);

/**
 * @brief Lock the EEPROM, preventing writes and erases.
 *
 * @return True if the command was successful (no timeout).
 */
bool ws_eeprom_write_lock(ws_eeprom_handle_t handle);

/**
 * @brief Unlock the EEPROM, allowing writes and erases.
 */
bool ws_eeprom_write_unlock(ws_eeprom_handle_t handle);

/**@}*/

/**
 * @addtogroup eeprom_ieep Internal EEPROM
 * @{
 */

/**
 * @brief Read the owner name, as raw data.
 *
 * @param data Target data area - must be at least 16 bytes.
 */
void ws_ieep_read_owner_name(uint8_t *data);

/**
 * @brief Read the owner name, as an ASCII string.
 * 
 * @param str Target string area - must be at least 17 bytes.
 */
void ws_ieep_read_owner_name_ascii(char *str);

/**
 * @brief Convert a given name color to its RGB value.
 * 
 * @param value The given name color.
 * @return uint16_t A 12-bit RGB value.
 */
uint16_t ws_ieep_name_color_to_rgb(uint8_t value);

/**
 * @brief Protect the non-cartridge area of the internal EEPROM.
 *
 * By default, the WonderSwan boot ROM protects the non-cartridge area of the internal EEPROM - addresses 0x60 and above - on boot.
 * By setting a bit in the cartridge's header (--unlock-ieep in swanlink), the non-cartridge area remains writable. In this case,
 * this function can be used to make the area read-only again.
 */
static inline void ws_ieep_set_protect(void) {
	outportb(WS_IEEP_CTRL_PORT, WS_IEEP_CTRL_PROTECT);
}

/**
 * @brief Check if the non-cartridge area of the internal EEPROM is currently protected.
 */
static inline bool ws_ieep_is_protected(void) {
	return inportb(WS_IEEP_CTRL_PORT) & WS_IEEP_CTRL_PROTECT;
}

/**@}*/

#endif /* __ASSEMBLER__ */

#endif /* LIBWS_EEPROM_H_ */
