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

#ifndef __WF_LIBWS_UTIL_H__
#define __WF_LIBWS_UTIL_H__

#include <stdint.h>
#include <wonderful.h>

/** \file util.h
 * Various utility functions for working with the WonderSwan hardware.
 */

static inline uint32_t ws_ptr_to_linear(const void __far* src) {
    return ((((uint32_t) src) >> 12) & 0xFFFF0) + ((uint16_t) ((uint32_t) src));
}

/**
 * @brief Copy memory data to I/O ports, in order.
 * 
 * @param port Destination port.
 * @param src Source pointer.
 * @param count Count, in bytes.
 */
void ws_portcpy(uint16_t port, const void __far* src, uint16_t count);

/**
 * @brief Busy wait.
 *
 * This is not recommended - use only when necessary!
 * Not halting the CPU can lead to higher power consumption.
 * The recommended approach is configuring an interrupt handler
 * and using cpu_halt() - which will then sleep until any interrupt
 * occurs.
 *
 * @param us Approximate number of microseconds.
 */
__attribute__((no_assume_ds_data, no_assume_ss_data))
void ws_busywait(uint16_t us);

#endif /* __WF_LIBWS_UTIL_H__ */
