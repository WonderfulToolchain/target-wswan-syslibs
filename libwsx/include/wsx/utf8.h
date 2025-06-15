/*
 * Copyright (c) 2024, 2025 Adrian "asie" Siekierka
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

#ifndef LIBWSX_UTF8_H_
#define LIBWSX_UTF8_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <wonderful.h>

/**
 * @brief Encode the next character in an UTF-8 string.
 * 
 * @param s Pointer to encode character to.
 * @param chr Character to encode.
 * @return char* Pointer to the first byte after the encoded character.
 */
char *wsx_utf8_encode_next(char *s, uint32_t chr);

/**
 * @brief Decode the next character in an UTF-8 string.
 * 
 * @param s Pointer to far pointer to character. Will be modified to point to the next character.
 * @return uint32_t The decoded character.
 */
uint32_t wsx_utf8_decode_next(const char __far** s);

/**
 * @brief Measure the length of an UTF-8 string, in characters.
 * 
 * @param s Pointer to UTF-8 string.
 * @return int Length of UTF-8 string, in characters; < 0 on error.
 */
int wsx_utf8_len(const char __far* s);

#ifdef __cplusplus
}
#endif

#endif /* LIBWSX_UTF8_H_ */
