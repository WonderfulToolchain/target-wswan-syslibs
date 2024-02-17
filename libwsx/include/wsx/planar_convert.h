/**
 * Copyright (c) 2024 Adrian "asie" Siekierka
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

#ifndef __WF_LIBWSX_PLANAR_CONVERT_H__
#define __WF_LIBWSX_PLANAR_CONVERT_H__

#include <stdint.h>

/** \file planar_convert.h
 * Planar image conversion routines.
 */

/**
 * @brief Convert a 4-bit packed row of eight pixels to a 4-bit planar row.
 */
uint32_t wsx_planar_convert_4bpp_packed_row(uint32_t row);

#endif /* __WF_LIBWSX_PLANAR_CONVERT_H__ */
