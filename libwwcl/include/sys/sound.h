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

/** \file sys/sound.h
 * FreyaBIOS sound calls.
 */

#ifndef __WF_LIBWW_SOUND_H__
#define __WF_LIBWW_SOUND_H__

#include "types.h"

/**
 * @addtogroup Int15 BIOS - INT 15h - Sound
 * @{
 */

void sound_init(void);
void sound_set_channel(uint8_t flags);
uint8_t sound_get_channel(void);
void sound_set_output(uint8_t flags);
uint8_t sound_get_output(void);
void sound_set_wave(uint8_t channel, const uint8_t __far* data);
void sound_set_pitch(uint8_t channel, uint16_t frequency);
uint16_t sound_get_pitch(uint8_t channel);
void sound_set_volume(uint8_t channel, uint8_t volume);
uint8_t sound_get_volume(uint8_t channel);
void sound_set_sweep(uint8_t sweep, uint8_t step_time);
void sound_set_noise(uint8_t flags);
uint8_t sound_get_noise(void);
uint16_t sound_get_random(void);

/* 0% volume (muted) */
#define SOUND_VOICE_MUTE 0
/* 50% volume */
#define SOUND_VOICE_HALF 2
/* 100% volume */
#define SOUND_VOICE_FULL 3

/**
 * Set channel 2 PCM volume.
 * @param left Left channel volume
 * @param right Right channel volume
 */
void sound_set_voice_volume(uint8_t left, uint8_t right);

/**
 * Get channel 2 PCM volume.
 * @return Bits 0-1 contain the right channel volume; bits 2-3 contain the left channel volume
 */
uint8_t sound_get_voice_volume(void);

/**@}*/

#endif /* __WF_LIBWW_SOUND_H__ */
