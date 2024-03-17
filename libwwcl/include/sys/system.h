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

/** \file sys/system.h
 * FreyaBIOS system calls.
 */

#ifndef __WF_LIBWW_SYSTEM_H__
#define __WF_LIBWW_SYSTEM_H__

#include "types.h"

/**
 * @addtogroup Int17 BIOS - INT 17h - System
 * @{
 */

struct intvector {
	void *callback;
	uint16_t cs;
	uint16_t ds;
	uint16_t unknown; /* ? */
};
typedef struct intvector intvector_t;

#define SYS_INT_SENDREADY      0x00
#define SYS_INT_KEY            0x01
#define SYS_INT_CASETTE        0x02
#define SYS_INT_RECEIVEREADY   0x03
#define SYS_INT_DISPLINE       0x04
#define SYS_INT_TIMER_COUNTUP  0x05
#define SYS_INT_VBLANK         0x06
#define SYS_INT_HBLANK_COUNTUP 0x07

void sys_interrupt_set_hook(uint8_t id, intvector_t *new_vector, intvector_t *old_vector);
void sys_interrupt_reset_hook(uint8_t id, intvector_t *old_vector);

void sys_wait(uint16_t v);

/**
 * @brief Read the current tick count.
 *
 * Under FreyaBIOS, one tick equals one frame. Note that the WonderSwan runs at 75Hz.  
 * 
 * @return uint32_t The current tick count.
 */
uint32_t sys_get_tick_count(void);

void sys_sleep(void);
void sys_set_sleep_time(uint16_t time);
uint16_t sys_get_sleep_time(void);
void sys_set_awake_key(uint16_t key);
uint16_t sys_get_awake_key(void);
void sys_set_keepalive_int(uint16_t value);
uint16_t sys_get_version(void);

/**@}*/

#endif /* __WF_LIBWW_SYSTEM_H__ */
