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

/** \file memory.h
 * Functionality related to memory and bank management.
 */

#ifndef LIBWS_MEMORY_H_
#define LIBWS_MEMORY_H_

#include <stdbool.h>
#include <stdint.h>
#include <wonderful.h>
#include "ports.h"
#include "util.h"

/**
 * @addtogroup memory Memory/Bank Management
 * @{
 */

/**
 * Address space for pointers to internal RAM.
 *
 * This is always a near pointer, either DS-indexed or SS-indexed.
 */
#define ws_iram __wf_iram

/**
 * Address space for pointers to cartridge SRAM.
 *
 * This can be a far or near pointer, depending on target.
 */
#define ws_sram __wf_sram

/**
 * Address space for pointers to read-only data.
 *
 * As this can be a far or near pointer - some targets store read-only
 * data in the data segment - this should not be used to mark pointers
 * to cartridge ROM.
 */
#define ws_rom __wf_rom

/**
 * Address space for all far pointers.
 */
#define ws_far __far

/**
 * Extract the 16-bit offset of any (near and/or far) pointer.
 */
#define ws_ptr_offset(x) ((uint16_t) (x))

/**
 * Extract the 16-bit segment of a far pointer.
 */
#define ws_ptr_segment(x) FP_SEG(x)

/**
 * Create a far pointer from a segment and offset value.
 */
#define ws_ptr_far(seg, ofs) MK_FP(seg, ofs)

/**
 * Convert a far pointer to a 20-bit linear address location.
 */
static inline uint32_t ws_ptr_to_linear(const void ws_far *src) {
    return ((((uint32_t) src) >> 12) & 0xFFFF0) + ((uint16_t) ((uint32_t) src));
}

/**
 * Convert a 20-bit linear address location to a far pointer.
 */
static inline const void ws_far *ws_ptr_from_linear(uint32_t src) {
    return ws_ptr_far(src >> 4, src & 0xF);
}

/**
 * Pointer to internal RAM memory.
 */
#define WS_IRAM_MEM ((uint8_t ws_iram*) 0x00000000)
/**
 * Pointer to the on-cartridge SRAM bank.
 */
#define WS_SRAM_MEM ((uint8_t ws_sram*) 0x10000000)
/**
 * Pointer to the on-cartridge ROM0 bank.
 */
#define WS_ROM0_MEM ((uint8_t __far*) 0x20000000)
/**
 * Pointer to the on-cartridge ROM1 bank.
 */
#define WS_ROM1_MEM ((uint8_t __far*) 0x30000000)

#ifdef LIBWS_USE_EXTBANK
typedef uint16_t ws_bank_t; ///< Type indicating a bank index.

/// \cond INTERNAL
static inline ws_bank_t _ws_bank_save(uint8_t port, ws_bank_t new_bank) {
	asm volatile("" ::: "memory");
	volatile ws_bank_t old_bank = inportw(port);
	outportw(port, new_bank);
	asm volatile("" ::: "memory");
	return old_bank;
}

static inline void _ws_bank_set(uint8_t port, ws_bank_t new_bank) {
	asm volatile("" ::: "memory");
	outportw(port, new_bank);
	asm volatile("" ::: "memory");
}

#define _ws_bank_ram_port WS_CART_EXTBANK_RAM_PORT
#define _ws_bank_rom0_port WS_CART_EXTBANK_ROM0_PORT
#define _ws_bank_rom1_port WS_CART_EXTBANK_ROM1_PORT
#define _ws_bank_roml_port WS_CART_EXTBANK_ROML_PORT
/// \endcond
#else
typedef uint8_t ws_bank_t; ///< Type indicating a bank index.

/// \cond INTERNAL
static inline ws_bank_t _ws_bank_save(uint8_t port, ws_bank_t new_bank) {
	asm volatile("" ::: "memory");
	volatile ws_bank_t old_bank = inportb(port);
	outportb(port, new_bank);
	asm volatile("" ::: "memory");
	return old_bank;
}

static inline void _ws_bank_set(uint8_t port, ws_bank_t new_bank) {
	asm volatile("" ::: "memory");
	outportb(port, new_bank);
	asm volatile("" ::: "memory");
}

#define _ws_bank_ram_port WS_CART_BANK_RAM_PORT
#define _ws_bank_rom0_port WS_CART_BANK_ROM0_PORT
#define _ws_bank_rom1_port WS_CART_BANK_ROM1_PORT
#define _ws_bank_roml_port WS_CART_BANK_ROML_PORT
/// \endcond
#endif

/// \cond INTERNAL
#define ws_bank_within_(var, loc, prev_bank, ...) \
	{ \
		extern const void __bank_ ## var; \
		ws_bank_t prev_bank = ws_bank_ ## loc ## _save((unsigned int) (&__bank_ ## var)); \
		__VA_ARGS__ \
		ws_bank_ram_restore(prev_bank); \
	}

#define ws_bank_with_(var, loc, prev_bank, ...) \
	{ \
		ws_bank_t prev_bank = ws_bank_ ## loc ## _save((unsigned int) var); \
		__VA_ARGS__ \
		ws_bank_ram_restore(prev_bank); \
	}
/// \endcond

/**
 * @brief Switch to a new RAM bank, while preserving the value of the old one.
 * 
 * @param new_bank New RAM bank.
 * @return uint8_t The previous RAM bank.
 */
#define ws_bank_ram_save(new_bank) _ws_bank_save(_ws_bank_ram_port, (new_bank))

/**
 * @brief Switch to a new RAM bank.
 * 
 * @param new_bank New RAM bank.
 */
#define ws_bank_ram_set(new_bank) _ws_bank_set(_ws_bank_ram_port, (new_bank))
#define ws_bank_ram_restore ws_bank_ram_set

/**
 * @brief Switch to the RAM bank containing the specified variable for a code block.
 *
 * This is equivalent to:
 * @code
 * extern const void __bank_var;
 * ws_bank_t previous_bank = ws_bank_ram_save(&__bank_var);
 * // ...
 * ws_bank_ram_restore(previous_bank);
 * @endcode
 * 
 * @param var The variable name.
 * @param ... The code block to run with the specified value in view.
 */
#define ws_bank_within_ram(var, ...) ws_bank_within_(var, ram WF_MACRO_CONCAT(_wf_bank_, __COUNTER__), __VA_ARGS__)

/**
 * @brief Switch to the specified RAM bank index for a code block.
 *
 * This is equivalent to:
 * @code
 * ws_bank_t previous_bank = ws_bank_ram_save(bank);
 * // ...
 * ws_bank_ram_restore(previous_bank);
 * @endcode
 * 
 * @param bank The bank index.
 * @param ... The code block to run with the specified value in view.
 */
#define ws_bank_with_ram(bank, ...) ws_bank_with_(bank, ram, WF_MACRO_CONCAT(_wf_bank_, __COUNTER__), __VA_ARGS__)

/**
 * @brief Switch to a new ROM bank in slot 0, while preserving the value of the old one.
 * 
 * @param new_bank New ROM bank.
 * @return uint8_t The previous ROM bank.
 */
#define ws_bank_rom0_save(new_bank) _ws_bank_save(_ws_bank_rom0_port, (new_bank))

/**
 * @brief Switch to a new ROM bank in slot 0.
 * 
 * @param new_bank New ROM bank.
 */
#define ws_bank_rom0_set(new_bank) _ws_bank_set(_ws_bank_rom0_port, (new_bank))
#define ws_bank_rom0_restore ws_bank_rom0_set

/**
 * @brief Switch to the ROM0 bank containing the specified variable for a code block.
 *
 * This is equivalent to:
 * @code
 * extern const void __bank_var;
 * ws_bank_t previous_bank = ws_bank_ram_save(&__bank_var);
 * // ...
 * ws_bank_ram_restore(previous_bank);
 * @endcode
 * 
 * @param var The variable name.
 * @param ... The code block to run with the specified value in view.
 */
#define ws_bank_within_rom0(var, ...) ws_bank_within_(var, rom0, WF_MACRO_CONCAT(_wf_bank_, __COUNTER__), __VA_ARGS__)

/**
 * @brief Switch to the specified ROM0 bank index for a code block.
 *
 * This is equivalent to:
 * @code
 * ws_bank_t previous_bank = ws_bank_ram_save(bank);
 * // ...
 * ws_bank_ram_restore(previous_bank);
 * @endcode
 * 
 * @param bank The bank index.
 * @param ... The code block to run with the specified value in view.
 */
#define ws_bank_with_rom0(bank, ...) ws_bank_within_(bank, rom0, WF_MACRO_CONCAT(_wf_bank_, __COUNTER__), __VA_ARGS__)

/**
 * @brief Switch to a new ROM bank in slot 1, while preserving the value of the old one.
 * 
 * @param new_bank New ROM bank.
 * @return uint8_t The previous ROM bank.
 */
#define ws_bank_rom1_save(new_bank) _ws_bank_save(_ws_bank_rom1_port, (new_bank))

/**
 * @brief Switch to a new ROM bank in slot 1.
 * 
 * @param new_bank New ROM bank.
 */
#define ws_bank_rom1_set(new_bank) _ws_bank_set(_ws_bank_rom1_port, (new_bank))
#define ws_bank_rom1_restore ws_bank_rom1_set

/**
 * @brief Switch to the ROM1 bank containing the specified variable for a code block.
 *
 * This is equivalent to:
 * @code
 * extern const void __bank_var;
 * ws_bank_t previous_bank = ws_bank_ram_save(&__bank_var);
 * // ...
 * ws_bank_ram_restore(previous_bank);
 * @endcode
 * 
 * @param var The variable name.
 * @param ... The code block to run with the specified value in view.
 */
#define ws_bank_within_rom1(var, ...) ws_bank_within_(var, rom1, WF_MACRO_CONCAT(_wf_bank_, __COUNTER__), __VA_ARGS__)

/**
 * @brief Switch to the specified ROM1 bank index for a code block.
 *
 * This is equivalent to:
 * @code
 * ws_bank_t previous_bank = ws_bank_ram_save(bank);
 * // ...
 * ws_bank_ram_restore(previous_bank);
 * @endcode
 * 
 * @param bank The bank index.
 * @param ... The code block to run with the specified value in view.
 */
#define ws_bank_with_rom1(bank, ...) ws_bank_with_(bank, rom1, WF_MACRO_CONCAT(_wf_bank_, __COUNTER__), __VA_ARGS__)

/**
 * @brief Switch to a new ROM bank in the linear slot, while preserving the value of the old one.
 * 
 * @param new_bank New ROM bank.
 * @return uint8_t The previous ROM bank.
 */
#define ws_bank_roml_save(new_bank) _ws_bank_save(_ws_bank_roml_port, (new_bank))

/**
 * @brief Switch to a new ROM bank in the linear slot.
 * 
 * @param new_bank New ROM bank.
 */
#define ws_bank_roml_set(new_bank) _ws_bank_set(_ws_bank_roml_port, (new_bank))
#define ws_bank_roml_restore ws_bank_roml_set

/**
 * @brief Switch to the ROML bank containing the specified variable for a code block.
 *
 * This is equivalent to:
 * @code
 * extern const void __bank_var;
 * ws_bank_t previous_bank = ws_bank_ram_save(&__bank_var);
 * // ...
 * ws_bank_ram_restore(previous_bank);
 * @endcode
 * 
 * @param var The variable name.
 * @param ... The code block to run with the specified value in view.
 */
#define ws_bank_within_roml(var, ...) ws_bank_within_(var, roml, WF_MACRO_CONCAT(_wf_bank_, __COUNTER__), __VA_ARGS__)

/**
 * @brief Switch to the specified ROML bank index for a code block.
 *
 * This is equivalent to:
 * @code
 * ws_bank_t previous_bank = ws_bank_ram_save(bank);
 * // ...
 * ws_bank_ram_restore(previous_bank);
 * @endcode
 * 
 * @param bank The bank index.
 * @param ... The code block to run with the specified value in view.
 */
#define ws_bank_with_roml(bank, ...) ws_bank_with_(bank, roml, WF_MACRO_CONCAT(_wf_bank_, __COUNTER__), __VA_ARGS__)

/**@}*/

#endif /* LIBWS_MEMORY_H_ */
