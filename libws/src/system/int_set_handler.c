/**
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

#include <stdbool.h>
#include <stdint.h>
#include <wonderful.h>
#include "ws/ports.h"
#include "ws/system.h"

void ws_int_set_handler(uint8_t idx, ia16_int_handler_t handler) {
    uint16_t __wf_iram* ptr = ((uint16_t __wf_iram*) (((inportb(WS_INT_VECTOR_PORT) & 0xF8) | idx) << 2));
    *(ptr++) = FP_OFF(handler);
    *(ptr++) = FP_SEG(handler);
}
