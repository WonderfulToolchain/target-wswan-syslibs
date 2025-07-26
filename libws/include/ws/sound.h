/*
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

/** \file sound.h
 * Functionality related to sound.
 */

#ifndef LIBWS_SOUND_H_
#define LIBWS_SOUND_H_

#ifndef __ASSEMBLER__
#include <stdbool.h>
#include <stdint.h>
#endif
#include "ports.h"
#include "util.h"
#include "system.h"

/**
 * @addtogroup sound Sound
 * @{
 */

/**
 * @brief Convert a frequency in hertz to a channel frequency value,
 * using the nearest approximation.
 *
 * Range: 1500 .. 3072000 Hz
 *
 * @param hz Playback frequency, in hertz.
 */
#define WS_SOUND_UPDATE_HZ_TO_FREQ(hz) (-((uint16_t) WS_HZ_TO_CLOCK_DIVIDER((hz), WS_SYSTEM_CLOCK_HZ)))

/**
 * @brief Convert a frequency in hertz to a channel frequency value for a wave sample
 * of a given length, using the nearest approximation.
 *
 * Range:
 *
 * 2-sample wave  -> 750 .. 1536000 Hz
 * 4-sample wave  -> 375 ..  768000 Hz
 * 8-sample wave  -> 188 ..  384000 Hz
 * 16-sample wave ->  94 ..  192000 Hz
 * 32-sample wave ->  47 ..   96000 Hz
 *
 * @param hz Playback frequency, in hertz.
 * @param length Length, in samples (2, 4, 8, 16, 32).
 */
#define WS_SOUND_WAVE_HZ_TO_FREQ(hz, length) (-((uint16_t) WS_HZ_TO_CLOCK_DIVIDER((hz), WS_SYSTEM_CLOCK_HZ / (length))))

/**
 * @brief Convert a frequency in hertz to a sweep channel update frequency value,
 * using the nearest approximation.
 * 
 * Range: 13 .. 375 Hz
 */
#define WS_SOUND_SWEEP_HZ_TO_FREQ(hz) ((uint16_t) WS_HZ_TO_CLOCK_DIVIDER((hz), WS_SYSTEM_CLOCK_HZ / 8192))

#ifndef __ASSEMBLER__

typedef struct {
    uint8_t data[16];
} ws_sound_wave_t;

typedef struct {
    ws_sound_wave_t wave[4];
} ws_sound_wavetable_t;

/**
 * @brief Reset the sound system.
 * 
 * Clears all sound-related I/O ports, except for the wave table address.
 */
void ws_sound_reset(void);

/**
 * @brief Set the base addresses of the sound wavetable.
 * 
 * @param address Pointer to sound wavetable data.
 */
static inline void ws_sound_set_wavetable_address(const void __wf_iram* address) {
	outportb(WS_SOUND_WAVE_BASE_PORT, WS_SOUND_WAVE_BASE_ADDR(address));
}

#endif

/**@}*/

#endif /* LIBWS_SOUND_H_ */
