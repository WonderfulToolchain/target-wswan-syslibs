/*
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

/** \file dma.h
 * Functionality related to DMA transfers.
 */

#ifndef LIBWS_DMA_H_
#define LIBWS_DMA_H_

#include <stdint.h>
#include <wonderful.h>
#include "ports.h"
#include "util.h"

/**
 * @addtogroup DMA Functions - DMA
 * @{
 */

static inline void ws_gdma_set_sourcep(const void __far *src) {
	outportw(WS_GDMA_SOURCE_L_PORT, (FP_SEG(src) << 4) + FP_OFF(src));
	outportb(WS_GDMA_SOURCE_H_PORT, FP_SEG(src) >> 12);
}

static inline void ws_gdma_set_sourcei(uint32_t src) {
	outportw(WS_GDMA_SOURCE_L_PORT, src);
	outportb(WS_GDMA_SOURCE_H_PORT, src >> 16);
}

#define ws_gdma_set_source(src) _Generic((src), \
	int8_t: ws_gdma_set_sourcei, \
	int16_t: ws_gdma_set_sourcei, \
	int32_t: ws_gdma_set_sourcei, \
	uint8_t: ws_gdma_set_sourcei, \
	uint16_t: ws_gdma_set_sourcei, \
	uint32_t: ws_gdma_set_sourcei, \
	default: ws_gdma_set_sourcep \
)(src)

static inline void ws_sdma_set_sourcep(const void __far *src) {
	outportw(WS_SDMA_SOURCE_L_PORT, (FP_SEG(src) << 4) + FP_OFF(src));
	outportb(WS_SDMA_SOURCE_H_PORT, FP_SEG(src) >> 12);
}

static inline void ws_sdma_set_sourcei(uint32_t src) {
	outportw(WS_SDMA_SOURCE_L_PORT, src);
	outportb(WS_SDMA_SOURCE_H_PORT, src >> 16);
}

#define ws_sdma_set_source(src) _Generic((src), \
	int8_t: ws_sdma_set_sourcei, \
	int16_t: ws_sdma_set_sourcei, \
	int32_t: ws_sdma_set_sourcei, \
	uint8_t: ws_sdma_set_sourcei, \
	uint16_t: ws_sdma_set_sourcei, \
	uint32_t: ws_sdma_set_sourcei, \
	default: ws_sdma_set_sourcep \
)(src)

static inline void ws_sdma_set_length(uint32_t length) {
	outportw(WS_SDMA_LENGTH_L_PORT, length);
	outportb(WS_SDMA_LENGTH_H_PORT, length >> 16);
}

void ws_gdma_copyi(void __wf_iram* dest, uint32_t src, uint16_t length);

static inline void ws_gdma_copyp(void __wf_iram* dest, const void __far* src, uint16_t length) {
	ws_gdma_copyi(dest, ws_ptr_to_linear(src), length);
}

/**
 * @brief Copy words from a source pointer to a destination pointer using DMA.
 * 
 * Note that this only works if Color mode is enabled - see @ref ws_system_is_color
 * For a function which works always, see @ref ws_gdma_maybe_copy
 *
 * @param dest Destination pointer, in RAM.
 * @param src Source linear (20-bit) address.
 * @param length Length, in bytes. Must be a multiple of 2.
 */
#define ws_gdma_copy(dest, src, length) _Generic((src), \
	int8_t: ws_gdma_copyi, \
	int16_t: ws_gdma_copyi, \
	int32_t: ws_gdma_copyi, \
	uint8_t: ws_gdma_copyi, \
	uint16_t: ws_gdma_copyi, \
	uint32_t: ws_gdma_copyi, \
	default: ws_gdma_copyp \
)(dest, src, length)

/**
 * @brief Copy words from a source pointer to a destination pointer, using DMA if present.
 *
 * @param dest Destination pointer, in RAM.
 * @param src Source pointer, in any location.
 * @param length Length, in bytes. Must be a multiple of 2.
 */
void ws_gdma_maybe_copy(void __wf_iram* dest, const void __far* src, uint16_t length);

/**@}*/

#endif /* LIBWS_DMA_H_ */
