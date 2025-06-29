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

#include <stdbool.h>
#include <stdint.h>
#include "ports.h"
#include "util.h"

/**
 * @addtogroup sound Sound
 * @{
 */

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

/**@}*/

#endif /* LIBWS_SOUND_H_ */
