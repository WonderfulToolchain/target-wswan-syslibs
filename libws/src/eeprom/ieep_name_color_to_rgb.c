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

#include <stdint.h>
#include "ws/display.h"
#include "ws/eeprom.h"

static const uint16_t
#ifdef __IA16_CMODEL_IS_FAR_TEXT
__far
#endif
ieep_name_color_to_rgb_map[16] = {
	WS_RGB(0, 0, 0),
	WS_RGB(15, 0, 0),
	WS_RGB(15, 7, 0),
	WS_RGB(15, 15, 0),
	WS_RGB(7, 15, 0),
	WS_RGB(0, 15, 0),
	WS_RGB(0, 15, 7),
	WS_RGB(0, 15, 15),
	WS_RGB(0, 7, 15),
	WS_RGB(0, 0, 15),
	WS_RGB(7, 0, 15),
	WS_RGB(15, 0, 15),
	WS_RGB(15, 0, 7),
	WS_RGB(15, 15, 15),
	WS_RGB(7, 7, 7),
	WS_RGB(7, 7, 7)
};

uint16_t ws_ieep_name_color_to_rgb(uint8_t value) {
	return ieep_name_color_to_rgb_map[value & 0x0F];
}
