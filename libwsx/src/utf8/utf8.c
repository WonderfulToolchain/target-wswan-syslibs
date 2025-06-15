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

#include <stdbool.h>
#include <stdint.h>
#include <wonderful.h>
#include "wsx/utf8.h"

char *wsx_utf8_encode_next(char *s, uint32_t chr) {
	if (chr < 0x80) {
		*(s++) = chr;
	} else if (chr < 0x7FF) {
		*(s++) = (chr >> 6) | 0xC0;
		*(s++) = (chr & 0x3F) | 0x80;
	} else if (chr < 0xFFFF) {
		*(s++) = (chr >> 12) | 0xE0;
		*(s++) = ((chr >> 6) & 0x3F) | 0x80;
		*(s++) = (chr & 0x3F) | 0x80;
	} else {
		*(s++) = (chr >> 18) | 0xF0;
		*(s++) = ((chr >> 12) & 0x3F) | 0x80;
		*(s++) = ((chr >> 6) & 0x3F) | 0x80;
		*(s++) = (chr & 0x3F) | 0x80;
	}
	return s;
}

#if 0

uint32_t wsx_utf8_decode_next(const char __far** s) {
	uint8_t c = *((*s)++);
	if (c < 0x80) {
		return c;
	} else if ((c & 0xE0) == 0xC0) {
		uint8_t c2 = *((*s)++);
		return ((c & 0x1F) << 6) | (c2 & 0x3F);
	} else if ((c & 0xF0) == 0xE0) {
		uint8_t c2 = *((*s)++);
		uint8_t c3 = *((*s)++);
		return (c << 12) | ((c2 & 0x3F) << 6) | (c3 & 0x3F);
	} else {
		uint8_t c2 = *((*s)++);
		uint8_t c3 = *((*s)++);
		uint8_t c4 = *((*s)++);
		return (c << 18) | ((c2 & 0x3F) << 12) | ((c3 & 0x3F) << 6) | (c4 & 0x3F);
	}
}

#endif
