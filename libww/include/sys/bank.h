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

/** \file sys/bank.h
 * FreyaBIOS cartridge calls.
 */

#ifndef __WF_LIBWW_BANK_H__
#define __WF_LIBWW_BANK_H__

#include <sys/types.h>

/**
 * @addtogroup Int18 BIOS - INT 18h - Cartridge bank management
 * @{
 */

static inline void bank_set_map(uint16_t bank_type, uint16_t bank) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x18"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x00), "b" (bank_type), "c" (bank)
		: "cc", "memory"
	);
}

static inline uint16_t bank_get_map(uint16_t bank_type) {
	uint16_t result;
	__asm volatile (
		"int $0x18"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x01), "b" (bank_type)
		: "cc", "memory"
	);
	return result;
}

static inline uint8_t bank_read_byte(uint16_t bank_id, uint16_t address) {
	uint16_t result;
	__asm volatile (
		"int $0x18"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x02), "b" (bank_id), "d" (address)
		: "cc", "memory"
	);
	return result;
}

static inline void bank_write_byte(uint16_t bank_id, uint16_t address, uint8_t value) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x18"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x03), "Rcl" (value), "b" (bank_id), "d" (address)
		: "cc", "memory"
	);
}

static inline uint16_t bank_read_word(uint16_t bank_id, uint16_t address) {
	uint16_t result;
	__asm volatile (
		"int $0x18"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x04), "b" (bank_id), "d" (address)
		: "cc", "memory"
	);
	return result;
}

static inline void bank_write_word(uint16_t bank_id, uint16_t address, uint16_t value) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x18"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x05), "b" (bank_id), "c" (value), "d" (address)
		: "cc", "memory"
	);
}

static inline void bank_read_block(uint16_t bank_id, uint16_t address, void __far* data, uint16_t length) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x18"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x06), "b" (bank_id), "c" (length), "d" (address), "S" (FP_OFF(data)), "Rds" (FP_SEG(data))
		: "cc", "memory"
	);
}

static inline void bank_write_block(uint16_t bank_id, uint16_t address, const void __far* data, uint16_t length) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x18"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x07), "b" (bank_id), "c" (length), "d" (address), "S" (FP_OFF(data)), "Rds" (FP_SEG(data))
		: "cc", "memory"
	);
}

static inline void bank_fill_block(uint16_t bank_id, uint16_t address, uint16_t length, uint8_t value) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x18"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x0800 | value)), "b" (bank_id), "c" (length), "d" (address)
		: "cc", "memory"
	);
}

static inline void bank_erase_flash(uint16_t bank_id) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x18"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x09), "b" (bank_id)
		: "cc", "memory"
	);
}

/**@}*/

#endif /* __WF_LIBWW_BANK_H__ */
