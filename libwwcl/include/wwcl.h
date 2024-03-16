/*
 * Copyright (c) 2024 Adrian "asie" Siekierka
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

/** \file sys/types.h
 * General system types.
 */

#ifndef __WF_WWCL_H__
#define __WF_WWCL_H__

#include <wonderful.h>
#include <ws.h>
#include "sys/bios.h"

#define WWCL_INIT_MODE(disp_ctrl, text_mode, scr1_addr, scr2_addr, spr_addr, reserved_name, reserved_from, reserved_to) \
    const uint8_t __wwcl_init_display_control = disp_ctrl; \
    const uint8_t __wwcl_init_scr_base = SCR1_BASE(scr1_addr) | SCR2_BASE(scr2_addr); \
    const uint8_t __wwcl_init_spr_base = SPR_BASE(spr_addr); \
    const uint8_t __wwcl_init_text_mode = text_mode; \
    __attribute__((section(reserved_name))) \
    const uint8_t __wwcl_reserved[(reserved_to) - (reserved_from)];

/**
 * @brief Init mode: screen 2 only, 256 tiles
 */
#define WWCL_INIT_MODE_ASCII1() \
    WWCL_INIT_MODE( \
        DISPLAY_SCR2_ENABLE, TEXT_MODE_ANK, \
        0x3000, 0x3000, 0x2E00, ".iramx_2e00", 0x2E00, 0x4000 \
    );

/**
 * @brief Init mode: screen 1 and 2, 256 tiles
 */
#define WWCL_INIT_MODE_ASCII2() \
    WWCL_INIT_MODE( \
        DISPLAY_SCR1_ENABLE | DISPLAY_SCR2_ENABLE, TEXT_MODE_ANK, \
        0x2800, 0x3000, 0x2600, ".iramx_2600", 0x2600, 0x4000 \
    );

/**
 * @brief Init mode: screen 2 only, 512 tiles
 */
#define WWCL_INIT_MODE_JAPANESE1() \
    WWCL_INIT_MODE( \
        DISPLAY_SCR2_ENABLE, TEXT_MODE_SJIS, \
        0x1800, 0x1800, 0x1600, ".iramx_1600", 0x1600, 0x4000 \
    );

/**
 * @brief Init mode: screen 1 and 2, 512 tiles
 */
#define WWCL_INIT_MODE_JAPANESE2() \
    WWCL_INIT_MODE( \
        DISPLAY_SCR2_ENABLE, TEXT_MODE_SJIS, \
        0x1000, 0x1800, 0x0E00, ".iramx_0e00", 0x0E00, 0x4000 \
    );

/**
 * @brief Initialize the libwwcl library using a memory layout mode.
 * 
 * Note that you need to use one of the WWCL_INIT_MODE macros for this call
 * to work properly.
 */
void wwcl_init(void);

/**
 * @brief Initialize the libwwcl library using a custom memory layout.
 * 
 * In this mode, display/sprite/sound functions will not work unless you
 * set IO_SCR_BASE, IO_SPR_BASE, etc. manually.
 */
void wwcl_init_custom(void);

#endif /* __WF_WWCL_H__ */
