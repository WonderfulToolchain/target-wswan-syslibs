/**
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

#include <stdio.h>
#include <string.h>
#include <wonderful.h>
#include <ws.h>
#include "wsx/console.h"
#include "ws/display.h"
#include "ws/system.h"
#include "wsx/zx0.h"

extern const uint8_t __wf_rom wsx_console_font_default[];
extern void wsx_libc_console_stdout;

typedef struct wsx_console_state {
    uint8_t x, y;
} wsx_console_state_t;

static wsx_console_config_t config;
static wsx_console_state_t state;

static inline uint16_t __wf_iram *console_get_screen_buffer(void) {
    return (uint16_t __wf_iram*) ((inportb(WS_SCR_BASE_PORT) >> config.screen) << 11);
}

static void wsx_console_sync_scroll(void) {
    ws_display_scroll_screen_to(config.screen >> 2, 0, ((state.y - (WS_DISPLAY_HEIGHT_TILES - 1)) << 3));
}

void wsx_console_putc(uint8_t c) {
    uint8_t oy = state.y;

    if (state.x >= WS_DISPLAY_WIDTH_TILES) {
        state.x = 0;
        state.y++;
        state.y &= 0x1F;
    }

    uint16_t __wf_iram *buf = console_get_screen_buffer();
    uint16_t tile = config.tile_offset | WS_SCREEN_ATTR_PALETTE(config.palette);

    switch (c) {
    case '\t': {
        uint8_t ox = state.x;
        state.x = (state.x + 4) & ~3;
        ws_screen_fill_tiles(buf, tile + 32 - config.char_start, ox, state.y, state.x - ox, 1);
    } break;
    case '\r': {
        state.x = 0;
    } break;
    case '\n': {
        state.x = 0;
        state.y++;
        state.y &= 0x1F;
    } break;
    default: {
        if (c >= config.char_start && c < (config.char_start + config.char_count)) {
            ws_screen_put_tile(buf, tile + c - config.char_start, state.x++, state.y);
        }
    } break;
    }

    if (oy != state.y) wsx_console_sync_scroll();
}

int _stdout_console_putc(uint8_t c, FILE *stream) {
    wsx_console_putc(c);
    return 0;
}

const struct wf_fileops_t ws_rom _wsx_libc_console_stdout_ops = {
    NULL,
    _stdout_console_putc
};

void wsx_console_clear(void) {
    ws_screen_fill_tiles(console_get_screen_buffer(), WS_SCREEN_ATTR_PALETTE(config.palette) + 32 - config.char_start, 
        0, 0, WS_DISPLAY_WIDTH_TILES, WS_SCREEN_HEIGHT_TILES);
}

void wsx_console_init(wsx_console_config_t __wf_cram *_config) {
    memcpy(&config, _config, sizeof(wsx_console_config_t));
    memset(&state, 0, sizeof(wsx_console_state_t));
    stdout = &wsx_libc_console_stdout;
    wsx_console_clear();
    wsx_console_sync_scroll();
}

void wsx_console_init_default(void __wf_iram *screen_buffer) {
    wsx_console_config_t config;
    config.tile_offset = 512 - 96;
    config.char_start = 32;
    config.char_count = 96;
    config.screen = WSX_CONSOLE_SCREEN1;
    config.palette = 0;

    outportw(WS_DISPLAY_CTRL_PORT, 0);

    if (ws_system_is_color_active()) {
        WS_DISPLAY_COLOR_MEM(0)[0] = 0xFFF;
        WS_DISPLAY_COLOR_MEM(0)[1] = 0x000;
    } else {
        ws_display_set_shade_lut(WS_DISPLAY_SHADE_LUT_DEFAULT);
        outportw(WS_SCR_PAL_0_PORT, WS_DISPLAY_MONO_PALETTE(0, 7, 0, 0));
    }

    ws_display_set_screen1_address(screen_buffer);
    wsx_zx0_decompress(WS_TILE_MEM(config.tile_offset), wsx_console_font_default);
    wsx_console_init(&config);

    outportw(WS_DISPLAY_CTRL_PORT, WS_DISPLAY_CTRL_SCR1_ENABLE | (0 << 8));
}