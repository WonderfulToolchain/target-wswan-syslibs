/*
 * Copyright (c) 2025 Adrian "asie" Siekierka
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

#ifndef LIBWS_TIMER_H_
#define LIBWS_TIMER_H_

/** \file timer.h
 * Functionality related to timers.
 */

#ifndef __ASSEMBLER__
#include <stdint.h>
#endif
#include <wonderful.h>
#include "ports.h"
#include "util.h"
#include "system.h"
#include "display.h"

/**
 * @addtogroup timer Timers
 * @{
 */

/**
 * @brief Convert a frequency in hertz to horizontal blank timer ticks.
 *
 * Range: 0.2 .. 12000 Hz
 *
 * @param hz Frequency, in hertz.
 */
#define WS_TIMER_HBLANK_HZ_TO_TICKS(hz) ((uint16_t) WS_HZ_TO_CLOCK_DIVIDER((hz), 12000))

/**
 * @brief Convert a frequency in hertz to vertical blank timer ticks.
 *
 * Range: 0.0012 .. 75.47 Hz
 *
 * @param hz Frequency, in hertz.
 */
#define WS_TIMER_VBLANK_HZ_TO_TICKS(hz) ((uint16_t) WS_HZ_TO_CLOCK_DIVIDER((hz), 12000 / (WS_DISPLAY_VTOTAL))))

#ifndef __ASSEMBLER__

static inline void ws_timer_hblank_disable(void) {
    outportb(WS_TIMER_CTRL_PORT, inportb(WS_TIMER_CTRL_PORT) & ~WS_TIMER_CTRL_HBL_MASK);
}

static inline void ws_timer_vblank_disable(void) {
    outportb(WS_TIMER_CTRL_PORT, inportb(WS_TIMER_CTRL_PORT) & ~WS_TIMER_CTRL_VBL_MASK);
}

/**
 * @brief Request a one-shot horizontal blank timer.
 * 
 * @param ticks The number of ticks to time.
 */
static inline void ws_timer_hblank_start_once(uint16_t ticks) {
    outportw(WS_TIMER_HBL_RELOAD_PORT, ticks);
    outportb(WS_TIMER_CTRL_PORT, (inportb(WS_TIMER_CTRL_PORT) & ~WS_TIMER_CTRL_HBL_MASK) | WS_TIMER_CTRL_HBL_ONESHOT);
}

/**
 * @brief Request a one-shot vertical blank timer.
 * 
 * @param ticks The number of ticks to time.
 */
static inline void ws_timer_vblank_start_once(uint16_t ticks) {
    outportw(WS_TIMER_VBL_RELOAD_PORT, ticks);
    outportb(WS_TIMER_CTRL_PORT, (inportb(WS_TIMER_CTRL_PORT) & ~WS_TIMER_CTRL_VBL_MASK) | WS_TIMER_CTRL_VBL_ONESHOT);
}

/**
 * @brief Request a repeating horizontal blank timer.
 * 
 * @param ticks The number of ticks to time.
 */
static inline void ws_timer_hblank_start_repeat(uint16_t ticks) {
    outportw(WS_TIMER_HBL_RELOAD_PORT, ticks);
    outportb(WS_TIMER_CTRL_PORT, (inportb(WS_TIMER_CTRL_PORT) & ~WS_TIMER_CTRL_HBL_MASK) | WS_TIMER_CTRL_HBL_REPEAT);
}

/**
 * @brief Request a repeating vertical blank timer.
 * 
 * @param ticks The number of ticks to time.
 */
static inline void ws_timer_vblank_start_repeat(uint16_t ticks) {
    outportw(WS_TIMER_VBL_RELOAD_PORT, ticks);
    outportb(WS_TIMER_CTRL_PORT, (inportb(WS_TIMER_CTRL_PORT) & ~WS_TIMER_CTRL_VBL_MASK) | WS_TIMER_CTRL_VBL_REPEAT);
}

#endif

/**@}*/

#endif /* LIBWS_TIMER_H_ */
