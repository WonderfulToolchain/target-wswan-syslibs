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
#include "ws/util.h"
#include "ws/ports.h"
#include "ws/dma.h"

void ws_dma_copy_words_linear(void __wf_iram* dest, uint32_t src, uint16_t length) {
	// This order of port writing provides the best code generation:
	// dest = AX, src = DX:CX, length = stack
	outportw(WS_GDMA_DEST_PORT, (uint16_t) dest);
	outportw(WS_GDMA_SOURCE_L_PORT, src);
	outportb(WS_GDMA_SOURCE_H_PORT, src >> 16);
	outportw(WS_GDMA_LENGTH_PORT, length);
	outportb(WS_GDMA_CTRL_PORT, WS_GDMA_CTRL_START);
}
