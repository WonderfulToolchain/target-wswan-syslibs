/**
 * Copyright (c) 2022, 2023 Adrian "asie" Siekierka
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
#include "ws/system.h"

bool ws_system_set_mode(ws_system_mode_t mode) {
	if (!ws_system_is_color_model()) {
		return mode == 0;
	}
	outportb(WS_SYSTEM_CTRL_COLOR_PORT, (inportb(WS_SYSTEM_CTRL_COLOR_PORT) & 0x1F) | mode);
	return true;
}

