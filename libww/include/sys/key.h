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

/** \file sys/key.h
 * FreyaBIOS keypad calls.
 */

#ifndef __WF_LIBWW_KEY_H__
#define __WF_LIBWW_KEY_H__

#include <sys/types.h>

/**
 * @addtogroup Int11 BIOS - INT 11h - Keypad
 * @{
 */

#define KEY_Y4    0x0800
#define KEY_Y3    0x0400
#define KEY_Y2    0x0200
#define KEY_Y1    0x0100
#define KEY_X4    0x0080
#define KEY_X3    0x0040
#define KEY_X2    0x0020
#define KEY_X1    0x0010
#define KEY_B     0x0008
#define KEY_A     0x0004
#define KEY_START 0x0002

#define KEY_UP1    KEY_X1
#define KEY_RIGHT1 KEY_X2
#define KEY_DOWN1  KEY_X3
#define KEY_LEFT1  KEY_X4
#define KEY_UP2    KEY_Y1
#define KEY_RIGHT2 KEY_Y2
#define KEY_DOWN2  KEY_Y3
#define KEY_LEFT2  KEY_Y4

static inline uint16_t key_press_check(void) {
	uint16_t result;
	__asm volatile (
		"int $0x11"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x00)
		: "cc", "memory"
	);
	return result;
}

static inline uint16_t key_hit_check(void) {
	uint16_t result;
	__asm volatile (
		"int $0x11"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x01)
		: "cc", "memory"
	);
	return result;
}

static inline uint16_t key_wait(void) {
	uint16_t result;
	__asm volatile (
		"int $0x11"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x02)
		: "cc", "memory"
	);
	return result;
}

static inline void key_set_repeat(uint8_t rate, uint8_t delay) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x11"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x03), "b" ((delay << 8) | rate)
		: "cc", "memory"
	);
}

// TODO: key_get_repeat (0x04)

static inline uint16_t key_hit_check_with_repeat(void) {
	uint16_t result;
	__asm volatile (
		"int $0x11"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x05)
		: "cc", "memory"
	);
	return result;
}

/**@}*/

#endif /* __WF_LIBW_KEY_H__ */
