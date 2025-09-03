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

#include <stdint.h>
#include "ws/ports.h"
#include "ws/display.h"

typedef struct {
    uint16_t entries[4];
} pal_2bpp_t;

void ws_display_palette_load_color_2bpp(const void __far* data, int first, int count) {
    const pal_2bpp_t __far *src = data;
    pal_2bpp_t __wf_iram *dest = (pal_2bpp_t __wf_iram*) WS_DISPLAY_COLOR_MEM(first);
    for (int i = 0; i < count; i++, src++, dest += 4) {
        *dest = *src;
    }
}