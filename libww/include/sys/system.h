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

#include <sys/types.h>

/**
 * @addtogroup Int17 BIOS - INT 17h - System
 * @{
 */

struct intvector {
	void (*callback)(void);
	uint16_t cs;
	uint16_t ds;
	uint16_t unknown; /* ? */
};
typedef struct intvector intvector_t;

struct ownerinfo {
	char name[16];
	uint16_t birth_year;
	uint8_t birth_month;
	uint8_t birth_day;
	uint8_t sex;
	uint8_t bloodtype;
};
typedef struct ownerinfo ownerinfo_t;

#define SYS_INT_SENDREADY      0x00
#define SYS_INT_KEY            0x01
#define SYS_INT_CASETTE        0x02
#define SYS_INT_RECEIVEREADY   0x03
#define SYS_INT_DISPLINE       0x04
#define SYS_INT_TIMER_COUNTUP  0x05
#define SYS_INT_VBLANK         0x06
#define SYS_INT_HBLANK_COUNTUP 0x07

static inline void sys_interrupt_set_hook(uint8_t id, intvector_t *new_vector, intvector_t *old_vector) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x17"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x0000 | id)), "b" (FP_OFF(new_vector)), "d" (FP_OFF(old_vector)), "Rds" (FP_SEG(new_vector))
		: "cc", "memory"
	);
}

static inline void sys_interrupt_reset_hook(uint8_t id, intvector_t *old_vector) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x17"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x0100 | id)), "b" (FP_OFF(old_vector)), "Rds" (FP_SEG(old_vector))
		: "cc", "memory"
	);
}

static inline void sys_wait(uint16_t v /* TODO */) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x17"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x02), "c" (v)
		: "cc", "memory"
	);
}

/**
 * @brief Read the current tick count.
 *
 * Under FreyaBIOS, one tick equals one frame. Note that the WonderSwan runs at 75Hz.  
 * 
 * @return uint32_t The current tick count.
 */
static inline uint32_t sys_get_tick_count(void) {
	uint32_t result;
	__asm volatile (
		"int $0x17"
		: "=A" (result)
		: "Rah" ((uint8_t) 0x03)
		: "cc", "memory"
	);
	return result;
}

static inline void sys_sleep(void) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x17"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x04)
		: "cc", "memory"
	);
}

static inline void sys_set_sleep_time(uint16_t time) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x17"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x05), "b" (time)
		: "cc", "memory"
	);
}

static inline uint16_t sys_get_sleep_time(void) {
	uint16_t result;
	__asm volatile (
		"int $0x17"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x06)
		: "cc", "memory"
	);
	return result;
}

static inline void sys_set_awake_key(uint16_t key) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x17"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x07), "b" (key)
		: "cc", "memory"
	);
}

static inline uint16_t sys_get_awake_key(void) {
	uint16_t result;
	__asm volatile (
		"int $0x17"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x08)
		: "cc", "memory"
	);
	return result;
}

static inline void sys_set_keepalive_int(uint16_t value) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x17"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x09), "b" (value)
		: "cc", "memory"
	);
}

static inline uint16_t sys_get_ownerinfo(uint16_t size, void __far* buffer) {
	uint16_t result;
	__asm volatile (
		"int $0x17"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x0A), "c" (size), "d" (FP_OFF(buffer)), "Rds" (FP_SEG(buffer))
		: "cc", "memory"
	);
	return result;
}

static inline void __wf_iram *sys_alloc_iram(void __far* ptr, uint16_t size) {
	uint16_t result;
	__asm volatile (
		"int $0x17"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x0F), "b" (FP_OFF(ptr)), "c" (size), "Rds" (FP_SEG(ptr))
		: "cc", "memory"
	);
	return (void __wf_iram*) result;
}

static inline void sys_free_iram(void __wf_iram* address) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x17"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x10), "b" (FP_OFF(address))
		: "cc", "memory"
	);
}

static inline void __wf_iram *sys_get_my_iram(void) {
	uint16_t result;
	__asm volatile (
		"int $0x17"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x11)
		: "cc", "memory"
	);
	return (void __wf_iram*) result;
}

static inline uint16_t sys_get_version(void) {
	uint16_t result;
	__asm volatile (
		"int $0x17"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x12)
		: "cc", "memory"
	);
	return result;
}

/**@}*/

#endif /* __WF_LIBWW_SYSTEM_H__ */
