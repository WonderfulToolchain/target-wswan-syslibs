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

#ifndef __WF_LIBWS_SYSTEM_H__
#define __WF_LIBWS_SYSTEM_H__

/** \file system.h
 * Functionality related to system control.
 */

/**
 * @addtogroup SystemControl Functions - System control
 * @{
 */

/**
 * UART TX ready interrupt.
 */
#define WS_INT_UART_TX 0
/**
 * Key scan column non-zero interrupt.
 */
#define WS_INT_KEY_SCAN 1
/**
 * Cartridge IRQ pin interrupt.
 */
#define WS_INT_CARTRIDGE 2
/**
 * UART RX ready interrupt.
 */
#define WS_INT_UART_RX 3
/**
 * Display line match interrupt.
 */
#define WS_INT_LINE_MATCH 4
/**
 * Vertical blank timer interrupt.
 */
#define WS_INT_VBL_TIMER 5
/**
 * Vertical blank interrupt.
 */
#define WS_INT_VBLANK 6
/**
 * Horizontal blank timer interrupt.
 */
#define WS_INT_HBL_TIMER 7

#ifndef __ASSEMBLER__

#include <stdbool.h>
#include <stdint.h>
#include <wonderful.h>
#include "util.h"
#include "ports.h"

/**
 * @brief Check if this device is capable of supporting Color mode (= is a WonderSwan Color or above).
 *
 * This is useful for gating functionality specific to Color mode - see @ref ws_system_mode_t for more information.
 * 
 * @return true This device is a WonderSwan Color or above.
 * @return false This device is a "mono" WonderSwan.
 */
static inline bool ws_system_is_color_model(void) {
	return inportb(WS_SYSTEM_CTRL_PORT) & WS_SYSTEM_CTRL_MODEL_COLOR;
}

/**
 * @brief Check if this device is currently in Color mode.
 *
 * @return true This device can currently access WonderSwan Color functionality.
 * @return false This device is limited to "mono" WonderSwan functionality.
 */
static inline bool ws_system_is_color_active(void) {
	return ws_system_is_color_model() && (inportb(WS_SYSTEM_CTRL_COLOR_PORT) & 0x80);
}

/**
 * @brief WonderSwan device model.
 */
typedef enum {
	/**
	 * @brief WonderSwan (mono).
	 */
	WS_MODEL_MONO = 0x00,

	/**
	 * @brief Pocket Challenge V2.
	 */
	WS_MODEL_PCV2 = 0x01,

	/**
	 * @brief WonderSwan Color.
	 */
	WS_MODEL_COLOR = 0x82,

	/**
	 * @brief SwanCrystal.
	 */
	WS_MODEL_CRYSTAL = 0x83,
} ws_system_model_t;

/**
 * @brief Get the device's model.
 * 
 * @return ws_system_model_t The device's model.
 */
ws_system_model_t ws_system_get_model(void);

/**
 * @brief WonderSwan system mode. 
 */
typedef enum {
	/**
	 * @brief Mono mode.
	 * 
	 * In this mode, the device acts like a "mono" WonderSwan. This is
	 * typically the default mode after boot.
	 */
	WS_MODE_MONO = 0x00,

	/**
	 * @brief Color mode.
	 * 
	 * In this mode, the device enables the functionality specific to the WonderSwan Color.
	 * The 2BPP tile area is utilized - only the first four colors of each palette are used.
	 */
	WS_MODE_COLOR = 0x80,

	/**
	 * @brief Color/4bpp mode.
	 * 
	 * In this mode, the device enables the functionality specific to the WonderSwan Color.
	 * The 4BPP tile area is utilized.
	 */
	WS_MODE_COLOR_4BPP = 0xC0,

	/**
	 * @brief Color/4bpp/Packed mode.
	 * 
	 * In this mode, the device enables the functionality specific to the WonderSwan Color.
	 * The 4BPP tile area is utilized. Tiles are stored in packed form - with two complete
	 * pixels per byte, as opposed to four separate consecutive planes.
	 */
	WS_MODE_COLOR_4BPP_PACKED = 0xE0
} ws_system_mode_t;

/**
 * @brief Get the current system mode.
 * 
 * @return ws_system_mode_t The current system mode.
 */
static inline ws_system_mode_t ws_system_get_mode(void) {
	return inportb(WS_SYSTEM_CTRL_COLOR_PORT) & 0xE0;
}

/**
 * @brief Set the new system mode.
 *
 * Note that any non-Mono modes require a WonderSwan Color or above - see @ref system_is_color
 * 
 * @param mode The new system mode.
 * @return true If the operation was successful.
 * @return false If the operation was unsuccessful (trying to apply a color mode on a "mono" WonderSwan).
 */
bool ws_system_set_mode(ws_system_mode_t mode);

/**
 * @brief Register a hardware interrupt handler.
 *
 * Note that hardware interrupts are level-triggered and thus must be acknowledged.
 * See @ref ws_int_ack for more information.
 * 
 * @param idx The interrupt (WS_INT_*)
 * @param handler The interrupt handler function.
 */
void ws_int_set_handler(uint8_t idx, ia16_int_handler_t handler);

/**
 * @brief Register a default interrupt handler for serial transmission.
 * This handler will automatically disable and acknowledge @ref HWINT_SERIAL_TX .
 */
void ws_int_set_default_handler_serial_tx(void);
/**
 * @brief Register a default, acknowledge-only interrupt handler.
 */
void ws_int_set_default_handler_key(void);
/**
 * @brief Register a default interrupt handler for serial receiving.
 * This handler will automatically disable and acknowledge @ref HWINT_SERIAL_RX .
 */
void ws_int_set_default_handler_serial_rx(void);
/**
 * @brief Register a default, acknowledge-only interrupt handler.
 */
void ws_int_set_default_handler_line(void);
/**
 * @brief Register a default, acknowledge-only interrupt handler.
 */
void ws_int_set_default_handler_vblank_timer(void);
/**
 * @brief Register a default, acknowledge-only interrupt handler.
 */
void ws_int_set_default_handler_vblank(void);
/**
 * @brief Register a default, acknowledge-only interrupt handler.
 */
void ws_int_set_default_handler_hblank_timer(void);

/**
 * @brief Set selected hardware interrupts.
 * 
 * @param mask The MASK of an interrupt (HWINT_*).
 */
static inline void ws_int_enable_set(uint8_t mask) {
	outportb(WS_INT_ENABLE_PORT, mask);
}

static inline uint8_t ws_int_enable_push(uint8_t mask) {
	uint8_t prev_mask = inportb(WS_INT_ENABLE_PORT);
	outportb(WS_INT_ENABLE_PORT, mask);
	return prev_mask;
}
#define ws_int_enable_pop ws_int_enable_set

/**
 * @brief Enable selected hardware interrupts.
 * 
 * @param mask The MASK of an interrupt (HWINT_*).
 */
void ws_int_enable(uint8_t mask);

/**
 * @brief Disable selected hardware interrupts.
 * 
 * @param mask The MASK of an interrupt (HWINT_*).
 */
void ws_int_disable(uint8_t mask);

/**
 * @brief Disable all hardware interrupts.
 */
static inline void ws_int_disable_all(void) {
	ws_int_disable(0xFF);
}

/**
 * @brief Acknowledge hardware interrupt.
 * 
 * @param mask The MASK of an interrupt (HWINT_*).
 */
static inline void ws_int_ack(uint8_t mask) {
	outportb(WS_INT_ACK_PORT, mask);
}

#endif

/**@}*/

#endif /* __WF_LIBWS_SYSTEM_H__ */
