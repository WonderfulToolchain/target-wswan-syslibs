/**
 * Copyright (C) 2019 Emmanuel Marty
 * Code modified for Wonderful toolchain
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
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
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef LIBWSX_APLIB_H_
#define LIBWSX_APLIB_H_

#include <stdint.h>

/** \file aplib.h
 * aPLib decompression routines.
 */

/**
 * @brief Decompress an aPLib-compressed buffer.
 *
 * @param dest Destination memory pointer.
 * @param src Source memory pointer.
 * @return The number of bytes decompressed.
 */
uint16_t wsx_aplib_decompress(void __far* dest, const void __far* src);

#endif /* LIBWSX_APLIB_H_ */
