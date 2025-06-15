/**
 * Copyright (c) 2024 Adrian "asie" Siekierka
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
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
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef LIBWSX_BCD_H_
#define LIBWSX_BCD_H_

#include <stdint.h>

/** \file bcd.h
 * BCD helper routines.
 */

/**
 * @brief Transform an 8-bit packed BCD number to an integer.
 *
 * @param value Packed BCD number.
 * @return Integer.
 */
uint8_t wsx_bcd8_to_int(uint8_t value);

/**
 * @brief Transform a 16-bit packed BCD number to an integer.
 *
 * @param value Packed BCD number.
 * @return Integer.
 */
uint16_t wsx_bcd16_to_int(uint16_t value);

/**
 * @brief Transform an 8-bit integer to a packed BCD number.
 *
 * @param value Integer.
 * @return Packed BCD number.
 */
uint8_t wsx_int_to_bcd8(uint8_t value);

#endif /* LIBWSX_BCD_H_ */
