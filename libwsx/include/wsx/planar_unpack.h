/**
 * Copyright (c) 2023 Adrian "asie" Siekierka
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

#pragma once
#include <stdint.h>

/** \file planar_unpack.h
 * Planar image unpacking routines.
 */

/**
 * @brief Unpack 1BPP tiles to 2BPP tiles, using color zero and a specified foreground color.
 */
#define WSX_PLANAR_UNPACK_1BPP_TO_2BPP_ZERO(fg) (fg)

/**
 * @brief Unpack 1BPP tiles to 4BPP tiles, using color zero and a specified foreground color.
 */
#define WSX_PLANAR_UNPACK_1BPP_TO_4BPP_ZERO(fg) ((fg) | (1 << 8))

/**
 * @brief Unpack 1BPP tiles to 2BPP tiles, using a specified background and foreground color.
 */
#define WSX_PLANAR_UNPACK_1BPP_TO_2BPP(bg, fg) ((fg) | ((bg) << 2) | (2 << 8))

/**
 * @brief Unpack a lower-bitdepth planar image to a higher bitdepth.
 *
 * @param dest Destination memory pointer.
 * @param src_length Source data length.
 * @param src Source memory pointer.
 * @param mode Unpacking mode, see WSX_PLANAR_UNPACK_MODE defines.
 */
void wsx_planar_unpack(void __far* dest, uint16_t src_length, const void __far* src, uint16_t mode);
