/*
 * Copyright (c) 2022, 2023 Adrian "asie" Siekierka
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

/** \file ia16.h
 * NEC V30MZ-related CPU defines
 */

#ifndef IA16_H_
#define IA16_H_

/**
 * @addtogroup IA16 NEC V30MZ CPU
 * @{
 */

/**
 * Divide error interrupt.
 */
#define IA16_INT_DIV    0
/**
 * Single step/break interrupt.
 */
#define IA16_INT_STEP   1
/**
 * Non-maskable interrupt.
 */
#define IA16_INT_NMI    2
/**
 * Breakpoint (INT3) interrupt.
 */
#define IA16_INT_BREAK  3
/**
 * Overflow (INTO) interrupt.
 */
#define IA16_INT_INTO   4
/**
 * Array bounds (BOUND) interrupt.
 */
#define IA16_INT_BOUNDS 5

/**
 * Carry flag.
 */
#define IA16_FLAG_CF 0x0001
/**
 * Parity flag.
 */
#define IA16_FLAG_PF 0x0004
/**
 * Auxillary carry flag.
 */
#define IA16_FLAG_AF 0x0010
/**
 * Zero flag.
 */
#define IA16_FLAG_ZF 0x0040
/**
 * Sign flag.
 */
#define IA16_FLAG_SF 0x0080
/**
 * Single step flag.
 */
#define IA16_FLAG_TF 0x0100
/**
 * Interrupt enable flag.
 */
#define IA16_FLAG_IF 0x0200
/**
 * Direction flag.
 */
#define IA16_FLAG_DF 0x0400
/**
 * Overflow flag.
 */
#define IA16_FLAG_OF 0x0800
/**
 * Mode flag.
 */
#define IA16_FLAG_MD 0x8000

#ifdef __ASSEMBLER__

#ifdef __IA16_CMODEL_IS_FAR_TEXT
#define IA16_RET retf
#define IA16_CALL_STACK_ARG(n) ((n)+4)

.macro IA16_CALL tgt:req
	.reloc	.+3, R_386_SEG16, "\tgt\()!"
	call 0:\tgt
.endm
.macro IA16_JMP tgt:req
	.reloc	.+3, R_386_SEG16, "\tgt\()!"
	jmp 0:\tgt
.endm
#else
#define IA16_RET ret
#define IA16_CALL_STACK_ARG(n) ((n)+2)

.macro IA16_CALL tgt:req
	call \tgt
.endm
.macro IA16_JMP tgt:req
	jmp \tgt
.endm
#endif

#else

#include <stdbool.h>
#include <stdint.h>

#define FP_SEG(x) __builtin_ia16_selector ((uint16_t) (((uint32_t) ((void __far*) (x))) >> 16))
#define FP_OFF(x) __builtin_ia16_FP_OFF ((x))
#define MK_FP(seg, ofs) ((void __far*) (((uint16_t) ofs) | (((uint32_t) ((uint16_t) seg)) << 16)))
#define _CS ia16_get_cs()
#define _DS ia16_get_ds()
#define _ES ia16_get_es()
#define _SS ia16_get_ss()

static inline __segment ia16_get_cs() {
	__segment result;
	__asm (
		"mov %%cs, %0"
		: "=r" (result)
	);
	return result;
}

#define ia16_get_ds __builtin_ia16_near_data_segment

static inline __segment ia16_get_es() {
	__segment result;
	__asm (
		"mov %%es, %0"
		: "=r" (result)
	);
	return result;
}

#define ia16_get_ss __builtin_ia16_ss

static inline uint16_t ia16_get_flags() {
	uint16_t result;
	__asm volatile (
		"pushf\npop %0"
		: "=r" (result)
	);
	return result;
}

static inline void ia16_set_flags(uint16_t flags) {
	__asm volatile (
		"push %0\npopf"
		: "r" (flags)
		: : "cc"
	);
}

 /**
  * @brief Read a byte from the given port.
  * 
  * @param port Port address
  * @return uint8_t The value read.
  */
static inline uint8_t inportb(uint8_t port) {
	uint8_t result;
	__asm volatile (
		"inb %1, %0"
		: "=Ral" (result)
		: "Nd" ((uint16_t) port)
	);
	return result;
}

 /**
  * @brief Read a word from the given port.
  * 
  * @param port Port address
  * @return uint8_t The value read.
  */
static inline uint16_t inportw(uint8_t port) {
	uint16_t result;
	__asm volatile (
		"inw %1, %0"
		: "=a" (result)
		: "Nd" ((uint16_t) port)
	);
	return result;
}

 /**
  * @brief Write a byte to the given port.
  * 
  * @param port Port address
  * @param value The value to write.
  */
static inline void outportb(uint8_t port, uint8_t value) {
	__asm volatile (
		"outb %0, %1"
		:
		: "Ral" (value), "Nd" ((uint16_t) port)
	);
}

 /**
  * @brief Write a word to the given port.
  * 
  * @param port Port address
  * @param value The value to write.
  */
static inline void outportw(uint8_t port, uint16_t value) {
	__asm volatile (
		"outw %0, %1"
		:
		: "a" (value), "Nd" ((uint16_t) port)
	);
}

static inline void ia16_halt(void) {
    __asm volatile ("hlt");
}

static inline void ia16_enable_irq(void) {
    __asm volatile ("sti");
}

static inline void ia16_disable_irq(void) {
    __asm volatile ("cli");
}

#define ia16_critical(...) \
	do { \
		ia16_disable_irq(); \
		__VA_ARGS__; \
		ia16_enable_irq(); \
	} while(0)

#endif

/**@}*/

#endif /* IA16_H_ */
