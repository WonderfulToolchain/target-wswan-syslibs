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

#pragma once

#define __WONDERFUL__

#ifndef __ia16__
/* __ia16__ is not defined - this means we're not running under gcc-ia16. */
/* Typically, this will imply a language server of some kind, like clangd. */
/* As such, define expected macros to paper over things (except __ia16__). */

/* Defines. */
#define __FAR
#define __SEG_SS
#define __SEG_CS
#define _M_IX86 100

#define __IA16_FEATURE_SHIFT_IMM
#define __IA16_FEATURE_PUSH_IMM
#define __IA16_FEATURE_IMUL_IMM
#define __IA16_FEATURE_PUSHA
#define __IA16_FEATURE_ENTER_LEAVE
#define __IA16_FEATURE_SHIFT_MASKED
#define __IA16_FEATURE_AAD_IMM

/* Do not set compiler feature defines - they are not supported under this */
/* environment. */

#define __IA16_ARCH_ANY
#define __IA16_ARCH_ANY_186
#define __IA16_ARCH_NEC_V30MZ

#define __IA16_TUNE_ANY
#define __IA16_TUNE_ANY_186
#define __IA16_TUNE_NEC_V30MZ

/* Also avoid mapping Open Watcom-specific compatibility macros - we do not */
/* want to encourage this. */

/* Pragmas. */
#define __far
#define __seg_ss
#define __seg_cs

#endif

#ifdef __ASSEMBLER__

/** Memory model helpers. */
#ifdef __IA16_CMODEL_IS_FAR_TEXT
#define ASM_PLATFORM_RET retf
#else
#define ASM_PLATFORM_RET ret
#endif

#ifdef __IA16_CMODEL_IS_FAR_TEXT
.macro ASM_PLATFORM_CALL tgt:req
	.reloc	.+3, R_386_SEG16, "\tgt\()!"
	call 0:\tgt
.endm

.macro ASM_PLATFORM_JMP tgt:req
	.reloc	.+3, R_386_SEG16, "\tgt\()!"
	jmp 0:\tgt
.endm
#else
.macro ASM_PLATFORM_CALL tgt:req
	call \tgt
.endm

.macro ASM_PLATFORM_JMP tgt:req
	jmp \tgt
.endm
#endif

#endif

#ifndef __ASSEMBLER__
#include <stdint.h>

/** IA-16 helpers. */
#define FP_SEG(x) __builtin_ia16_selector ((uint16_t) (((uint32_t) ((void __far*) (x))) >> 16))
#define FP_OFF(x) __builtin_ia16_FP_OFF ((x))
#define MK_FP(seg, ofs) ((void __far*) (((uint16_t) ofs) | (((uint32_t) ((uint16_t) seg)) << 16)))
#define _CS __builtin_wonderful_cs()
#define _DS __builtin_wonderful_ds()
#define _ES __builtin_wonderful_es()
#define _SS __builtin_wonderful_ss()

static inline uint16_t __builtin_wonderful_cs() {
	uint16_t result;
	__asm (
		"mov %%cs, %0"
		: "=r" (result)
	);
	return result;
}

static inline uint16_t __builtin_wonderful_ds() {
	uint16_t result;
	__asm (
		"mov %%ds, %0"
		: "=r" (result)
	);
	return result;
}

static inline uint16_t __builtin_wonderful_es() {
	uint16_t result;
	__asm (
		"mov %%es, %0"
		: "=r" (result)
	);
	return result;
}

static inline uint16_t __builtin_wonderful_ss() {
	uint16_t result;
	__asm (
		"mov %%ss, %0"
		: "=r" (result)
	);
	return result;
}

 /**
  * @brief Read a byte from the given port.
  * 
  * @param port Port ID. For more information, see @ref DefinesIOPorts
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
  * @param port Port ID. For more information, see @ref DefinesIOPorts
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
  * @param port Port ID. For more information, see @ref DefinesIOPorts
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
  * @param port Port ID. For more information, see @ref DefinesIOPorts
  * @param value The value to write.
  */
static inline void outportw(uint8_t port, uint16_t value) {
	__asm volatile (
		"outw %0, %1"
		:
		: "a" (value), "Nd" ((uint16_t) port)
	);
}

static inline void cpu_halt(void) {
	__asm volatile ("hlt");
}
#define hlt cpu_halt

static inline void cpu_irq_enable(void) {
	__asm volatile ("sti");
}
#define sti cpu_irq_enable

static inline void cpu_irq_disable(void) {
	__asm volatile ("cli");
}
#define cli cpu_irq_disable

#endif
