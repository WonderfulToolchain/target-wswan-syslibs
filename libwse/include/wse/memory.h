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

#ifndef LIBWSE_WSE_MEMORY_H_
#define LIBWSE_WSE_MEMORY_H_

#include <wonderful.h>
#include <ws.h>

/**
 * @brief Reserve space for a given number of 2BPP and 4BPP tiles.
 * @param count_2bpp Number of 2 bits-per-pixel tiles (0 - 1024)
 * @param count_4bpp Number of 4 bits-per-pixel tiles (0 - 1024)
 */
#define WSE_RESERVE_TILES(count_2bpp, count_4bpp) \
asm(" .section .iramx_2000.__wse_tiles_2bpp, \"aR\"\n" \
    " .global __wse_tiles_2bpp\n" \
    "__wse_tiles_2bpp:\n" \
    " .if " #count_2bpp " >= 512\n" \
    "   .fill 512*16\n" \
    " .else\n" \
    "   .fill (" #count_2bpp ")*16\n" \
    " .endif\n\n" \
    " .section .iramx_4000.__wse_tiles_4bpp, \"aR\"\n" \
    " .global __wse_tiles_4bpp\n" \
    "__wse_tiles_4bpp:\n" \
    " .if (" #count_4bpp ")*2 > (" #count_2bpp ")-512\n" \
    "   .fill (" #count_4bpp ")*32\n" \
    " .else\n" \
    "   .fill ((" #count_2bpp ")-512)*16\n" \
    " .endif\n ")

extern ws_screen_t ws_iram wse_screen1;
extern ws_screen_t ws_iram wse_screen2;
extern ws_screen_t ws_iram wse_screen3;
extern ws_screen_t ws_iram wse_screen4;
extern ws_screen_t ws_iram wse_screen5;
extern ws_screen_t ws_iram wse_screen6;
extern ws_screen_t ws_iram wse_screen7;
extern ws_screen_t ws_iram wse_screen8;

extern ws_sprite_table_t ws_iram wse_sprites1;
extern ws_sprite_table_t ws_iram wse_sprites2;
extern ws_sprite_table_t ws_iram wse_sprites3;
extern ws_sprite_table_t ws_iram wse_sprites4;
extern ws_sprite_table_t ws_iram wse_sprites5;
extern ws_sprite_table_t ws_iram wse_sprites6;
extern ws_sprite_table_t ws_iram wse_sprites7;
extern ws_sprite_table_t ws_iram wse_sprites8;

extern ws_sound_wavetable_t ws_iram wse_wavetable1;
extern ws_sound_wavetable_t ws_iram wse_wavetable2;
extern ws_sound_wavetable_t ws_iram wse_wavetable3;
extern ws_sound_wavetable_t ws_iram wse_wavetable4;
extern ws_sound_wavetable_t ws_iram wse_wavetable5;
extern ws_sound_wavetable_t ws_iram wse_wavetable6;
extern ws_sound_wavetable_t ws_iram wse_wavetable7;
extern ws_sound_wavetable_t ws_iram wse_wavetable8;

#endif /* LIBWSE_WSE_MEMORY_H_ */
