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

/** \file cartridge.h
 * Functionality related to the cartridge.
 */

#ifndef __WF_LIBWS_CARTRIDGE_H__
#define __WF_LIBWS_CARTRIDGE_H__

#include <stdbool.h>
#include <stdint.h>
#include <wonderful.h>
#include "hardware.h"
#include "util.h"

typedef uint8_t ws_bank_t;

#define WF_BANK_INDEX(x) (x)

/**
 * @addtogroup DefinesMemoryLayout Defines - Memory layout
 * @{
 */

#define MEM_RAM ((uint8_t __wf_iram*) 0x00000000)
#define MEM_SRAM ((uint8_t __far*) 0x10000000)
#define MEM_ROM0 ((uint8_t __far*) 0x20000000)
#define MEM_ROM1 ((uint8_t __far*) 0x30000000)
#define MEM_ROM_LINEAR ((uint8_t __far*) 0x40000000)

/**@}*/

/**
 * @addtogroup Cartridge Functions - Cartridge/Banking
 * @{
 */

static inline ws_bank_t __ws_bank_save(uint8_t port, ws_bank_t new_bank) {
	asm volatile("" ::: "memory");
	uint8_t old_bank = inportb(port);
	outportb(port, new_bank);
	asm volatile("" ::: "memory");
	return old_bank;
}

static inline ws_bank_t __ws_bank_savep(uint8_t port, const void *faux_bank_ptr) {
	return __ws_bank_save(port, (uint8_t) ((uint16_t) faux_bank_ptr));
}

static inline void __ws_bank_set(uint8_t port, ws_bank_t new_bank) {
	asm volatile("" ::: "memory");
	outportb(port, new_bank);
	asm volatile("" ::: "memory");
}

static inline void __ws_bank_setp(uint8_t port, const void *faux_bank_ptr) {
	__ws_bank_set(port, (uint8_t) ((uint16_t) faux_bank_ptr));
}

/**
 * @brief Switch to a new RAM bank, while preserving the value of the old one.
 * 
 * @param new_bank New RAM bank.
 * @return uint8_t The previous RAM bank.
 */
#define ws_bank_ram_save(new_bank) _Generic((new_bank), \
	const void*: __ws_bank_savep, \
	default: __ws_bank_save)(IO_BANK_RAM, new_bank)

/**
 * @brief Switch to a new RAM bank.
 * 
 * @param new_bank New RAM bank.
 */
#define ws_bank_ram_set(new_bank) _Generic((new_bank), \
	const void*: __ws_bank_setp, \
	default: __ws_bank_set)(IO_BANK_RAM, new_bank)

#define ws_bank_ram_restore ws_bank_ram_set

/**
 * @brief Switch to a new ROM bank in slot 0, while preserving the value of the old one.
 * 
 * @param new_bank New ROM bank.
 * @return uint8_t The previous ROM bank.
 */
#define ws_bank_rom0_save(new_bank) _Generic((new_bank), \
	const void*: __ws_bank_savep, \
	default: __ws_bank_save)(IO_BANK_ROM0, new_bank)

/**
 * @brief Switch to a new ROM bank in slot 0.
 * 
 * @param new_bank New ROM bank.
 */
#define ws_bank_rom0_set(new_bank) _Generic((new_bank), \
	const void*: __ws_bank_setp, \
	default: __ws_bank_set)(IO_BANK_ROM0, new_bank)

#define ws_bank_rom0_restore ws_bank_rom0_set

/**
 * @brief Switch to a new ROM bank in slot 1, while preserving the value of the old one.
 * 
 * @param new_bank New ROM bank.
 * @return uint8_t The previous ROM bank.
 */
#define ws_bank_rom1_save(new_bank) _Generic((new_bank), \
	const void*: __ws_bank_savep, \
	default: __ws_bank_save)(IO_BANK_ROM1, new_bank)

/**
 * @brief Switch to a new ROM bank in slot 1.
 * 
 * @param new_bank New ROM bank.
 */
#define ws_bank_rom1_set(new_bank) _Generic((new_bank), \
	const void*: __ws_bank_setp, \
	default: __ws_bank_set)(IO_BANK_ROM1, new_bank)

#define ws_bank_rom1_restore ws_bank_rom1_set

/**
 * @brief Switch to a new ROM bank in the linear slot, while preserving the value of the old one.
 * 
 * @param new_bank New ROM bank.
 * @return uint8_t The previous ROM bank.
 */
#define ws_bank_rom_linear_save(new_bank) _Generic((new_bank), \
	const void*: __ws_bank_savep, \
	default: __ws_bank_save)(IO_BANK_ROM_LINEAR, new_bank)

/**
 * @brief Switch to a new ROM bank in the linear slot.
 * 
 * @param new_bank New ROM bank.
 */
#define ws_bank_rom_linear_set(new_bank) _Generic((new_bank), \
	const void*: __ws_bank_setp, \
	default: __ws_bank_set)(IO_BANK_ROM_LINEAR, new_bank)

#define ws_bank_rom_linear_restore ws_bank_rom_linear_set

/**
 * @brief Enable general-purpose output.
 * 
 * @param id General-purpose output ID (0-3)
 */
void ws_cart_gpo_enable(uint8_t id);

/**
 * @brief Disable general-purpose output.
 * 
 * @param id General-purpose output ID (0-3)
 */
void ws_cart_gpo_disable(uint8_t id);

/**
 * @brief Set general-purpose output value.
 * 
 * @param id General-purpose output ID (0-3)
 * @param val Value (true or false).
 */
void ws_cart_gpo_set(uint8_t id, bool val);

/**@}*/

#endif /* __WF_LIBWS_CARTRIDGE_H__ */
