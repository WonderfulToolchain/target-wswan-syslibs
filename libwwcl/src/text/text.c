/**
 * Copyright (c) 2023, 2024 Adrian "asie" Siekierka
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

#include <string.h>
#include <wonderful.h>
#include <ws.h>
#include "sys/bios.h"

uint8_t __wwcl_text_screen = 1;
uint8_t __wwcl_text_mode;
uint8_t __wwcl_text_palette = 0;
uint8_t __wwcl_text_wx, __wwcl_text_wy, __wwcl_text_ww, __wwcl_text_wh;
uint16_t __wwcl_text_base;

extern const uint8_t __wf_rom __wwcl_font_ank[];

#define text_screen __wwcl_text_screen
#define text_mode __wwcl_text_mode
#define window_x __wwcl_text_wx
#define window_y __wwcl_text_wy
#define window_width __wwcl_text_ww
#define window_height __wwcl_text_wh
#define text_base __wwcl_text_base
#define text_palette __wwcl_text_palette
#define TEXT_TILEMAP_AT(x, y) (text_tilemap() + ((y) * 32) + (x))
#define TEXT_FONTMAP_AT(x, y) (text_fontmap() + ((y) * window_width) + (x))

static uint16_t *text_tilemap(void) {
    uint8_t shift = __wwcl_text_screen ? 4 : 0;
    return (uint16_t*) (((inportb(IO_SCR_BASE) >> shift) & 0xF) << 11);
}

static ws_display_tile_t *text_fontmap(void) {
    return (ws_display_tile_t*) (0x2000 + (text_base << 4));
}

static void text_window_clear_screen(void) {
    if (text_mode == TEXT_MODE_ANK) {
        screen_fill_char(text_screen,
            window_x, window_y,
            window_width, window_height, text_base | SCR_ENTRY_PALETTE(text_palette));
    } else {
        int i = text_base | SCR_ENTRY_PALETTE(text_palette);
        uint16_t *tilemap = text_tilemap() + (window_y * 32) + window_x;
        for (int iy = 0; iy < window_height; iy++, tilemap += 32) {
            for (int ix = 0; ix < window_width; ix++) {
                tilemap[ix] = i++;
            }
        }
    }
}

static void text_window_init_tiles(void) {
    if (text_mode == TEXT_MODE_ANK) {
        font_set_monodata(text_base, 128, __wwcl_font_ank);
    } else {
        memset(text_fontmap(), 0, window_width * window_height * sizeof(ws_display_tile_t));
    }
}

void text_screen_init(void) {
    text_window_init(0, 0, 28, 18, text_mode == TEXT_MODE_ANK ? 384 : 0);
}

void text_window_init(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t base) {
    window_x = x;
    window_y = y;
    window_width = width;
    window_height = height;
    text_base = base;
    
    text_window_init_tiles();
    text_window_clear_screen();
}

#ifndef __IA16_CMODEL_TINY__
extern const uint16_t __wf_rom __wwcl_ank_sjis_table[];
#endif

void text_put_char(uint8_t x, uint8_t y, uint16_t chr) {
    if (x >= window_width || y >= window_height) return;

    if (text_mode == TEXT_MODE_ANK) {
        if (chr >= 0x80) chr = '?';
        *TEXT_TILEMAP_AT(x, y) = (text_base + chr) | SCR_ENTRY_PALETTE(text_palette);
    } else {
#ifndef __IA16_CMODEL_TINY__
        // Convert ASCII character to SJIS range, if necessary
        if (text_mode == TEXT_MODE_SJIS && chr >= 0x20 && chr < 0x7F) {
            chr = __wwcl_ank_sjis_table[chr - 0x20];
        }
#endif
        uint8_t data[8];
        memset(data, 0, sizeof(data));
        text_get_fontdata(chr, data);
        font_set_monodata(text_base + y * window_width + x, 1, data);
    }
}

uint16_t text_put_substring(uint8_t x, uint8_t y, const char __far* str, uint16_t length) {
    // TODO: Does this wrap around?
    while (*str && length--) {
        uint16_t ch = *(str++);
        if (text_mode >= TEXT_MODE_ANK_SJIS && ch >= 0x80) {
            if (!(*str)) break;
            ch = (ch << 8) | *(str++);
        }
        text_put_char(x++, y, ch);
    }
    return 0; // TODO
}

uint16_t text_put_string(uint8_t x, uint8_t y, const char __far* str) {
    return text_put_substring(x, y, str, 65535);
}

uint16_t text_fill_char(uint8_t x, uint8_t y, uint16_t length, uint16_t chr) {
    while (length--) {
        text_put_char(x++, y, chr);
    }
    return 0; // TODO
}

void text_set_screen(uint8_t screen_id) {
    text_screen = screen_id;
}

uint16_t text_get_screen(void) {
    return text_screen;
}

void text_set_mode(uint16_t mode) {
    text_mode = mode;
}

uint16_t text_get_mode(void) {
    return text_mode;
}

void text_set_palette(uint16_t palette) {
    text_palette = palette;
}

uint16_t text_get_palette(void) {
    return text_palette;
}
