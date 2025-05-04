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
#include "ports.h"
#include "util.h"

#define WF_BANK_INDEX(x) (x)

/**
 * @addtogroup Cartridge Functions - Cartridge/Banking
 * @{
 */

/**
 * Pointer to internal RAM memory.
 */
#define WS_IRAM ((uint8_t __wf_iram*) 0x00000000)
/**
 * Pointer to the on-cartridge SRAM bank.
 */
#define WS_SRAM ((uint8_t __wf_sram*) 0x10000000)
/**
 * Pointer to the on-cartridge ROM0 bank.
 */
#define WS_ROM0 ((uint8_t __far*) 0x20000000)
/**
 * Pointer to the on-cartridge ROM1 bank.
 */
#define WS_ROM1 ((uint8_t __far*) 0x30000000)

#ifdef LIBWS_USE_BANKEXT
typedef uint16_t ws_bank_t;

static inline ws_bank_t __ws_bank_save(uint8_t port, ws_bank_t new_bank) {
	asm volatile("" ::: "memory");
	volatile ws_bank_t old_bank = inportw(port);
	outportw(port, new_bank);
	asm volatile("" ::: "memory");
	return old_bank;
}

static inline void __ws_bank_set(uint8_t port, ws_bank_t new_bank) {
	asm volatile("" ::: "memory");
	outportw(port, new_bank);
	asm volatile("" ::: "memory");
}
#else
typedef uint8_t ws_bank_t;

static inline ws_bank_t __ws_bank_save(uint8_t port, ws_bank_t new_bank) {
	asm volatile("" ::: "memory");
	volatile ws_bank_t old_bank = inportb(port);
	outportb(port, new_bank);
	asm volatile("" ::: "memory");
	return old_bank;
}

static inline void __ws_bank_set(uint8_t port, ws_bank_t new_bank) {
	asm volatile("" ::: "memory");
	outportb(port, new_bank);
	asm volatile("" ::: "memory");
}
#endif

/**
 * @brief Switch to a new RAM bank, while preserving the value of the old one.
 * 
 * @param new_bank New RAM bank.
 * @return uint8_t The previous RAM bank.
 */
#define ws_bank_ram_save(new_bank) __ws_bank_save(WS_CART_BANK_RAM_PORT, (new_bank))

/**
 * @brief Switch to a new RAM bank.
 * 
 * @param new_bank New RAM bank.
 */
#define ws_bank_ram_set(new_bank) __ws_bank_set(WS_CART_BANK_RAM_PORT, (new_bank))
#define ws_bank_ram_restore ws_bank_ram_set

/**
 * @brief Switch to a new ROM bank in slot 0, while preserving the value of the old one.
 * 
 * @param new_bank New ROM bank.
 * @return uint8_t The previous ROM bank.
 */
#define ws_bank_rom0_save(new_bank) __ws_bank_save(WS_CART_BANK_ROM0_PORT, (new_bank))

/**
 * @brief Switch to a new ROM bank in slot 0.
 * 
 * @param new_bank New ROM bank.
 */
#define ws_bank_rom0_set(new_bank) __ws_bank_set(WS_CART_BANK_ROM0_PORT, (new_bank))
#define ws_bank_rom0_restore ws_bank_rom0_set

/**
 * @brief Switch to a new ROM bank in slot 1, while preserving the value of the old one.
 * 
 * @param new_bank New ROM bank.
 * @return uint8_t The previous ROM bank.
 */
#define ws_bank_rom1_save(new_bank) __ws_bank_save(WS_CART_BANK_ROM1_PORT, (new_bank))

/**
 * @brief Switch to a new ROM bank in slot 1.
 * 
 * @param new_bank New ROM bank.
 */
#define ws_bank_rom1_set(new_bank) __ws_bank_set(WS_CART_BANK_ROM1_PORT, (new_bank))
#define ws_bank_rom1_restore ws_bank_rom1_set

/**
 * @brief Switch to a new ROM bank in the linear slot, while preserving the value of the old one.
 * 
 * @param new_bank New ROM bank.
 * @return uint8_t The previous ROM bank.
 */
#define ws_bank_roml_save(new_bank) __ws_bank_save(WS_CART_BANK_ROML_PORT, (new_bank))

/**
 * @brief Switch to a new ROM bank in the linear slot.
 * 
 * @param new_bank New ROM bank.
 */
#define ws_bank_roml_set(new_bank) __ws_bank_set(WS_CART_BANK_ROML_PORT, (new_bank))
#define ws_bank_roml_restore ws_bank_roml_set

#define WS_CART_GPIO_PIN(n) (1 << (n))
#define WS_CART_GPIO_PIN_0 0x01
#define WS_CART_GPIO_PIN_1 0x02
#define WS_CART_GPIO_PIN_2 0x04
#define WS_CART_GPIO_PIN_3 0x08

void ws_cart_gpio_set_output(uint8_t mask);
void ws_cart_gpio_set_input(uint8_t mask);
void ws_cart_gpio_set(uint8_t mask);
void ws_cart_gpio_clear(uint8_t mask);

/**@}*/

#endif /* __WF_LIBWS_CARTRIDGE_H__ */
