/**
 * Copyright (c) 2025 Adrian "asie" Siekierka
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
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
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef LIBWSX_CONSOLE_H_
#define LIBWSX_CONSOLE_H_

#include <stdint.h>
#include <wonderful.h>
#include <ws.h>

/** \file console.h
 * Text console implementation.
 */

#define WSX_CONSOLE_SCREEN1 0
#define WSX_CONSOLE_SCREEN2 4

typedef struct wsx_console_config {
    uint16_t tile_offset; ///< The index of the first tile used by the console.
    uint8_t char_start; ///< The character represented by the first tile.
    uint8_t char_count; ///< The number of characters represented by the tileset. (0 means 256)
    uint8_t screen; ///< Screen to use (WSX_CONSOLE_SCREEN1 or WSX_CONSOLE_SCREEN2).
    uint8_t palette; ///< Palette index to use (0-15).
} wsx_console_config_t;

void wsx_console_putc(uint8_t c);
void wsx_console_clear(void);
void wsx_console_init(wsx_console_config_t __wf_cram *config);
void wsx_console_init_default(void __wf_iram *screen_buffer);

#endif /* LIBWSX_CONSOLE_H_ */
