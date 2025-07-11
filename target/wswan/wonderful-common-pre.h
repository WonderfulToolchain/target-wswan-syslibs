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

#if defined(__CLANGD__) || !defined(__ia16__)
/* If __ia16__ is not defined, assume a language server of some kind which */
/* does not support querying ia16-elf-gcc. */
#define __WF_LS_NO_DEFINE_SUPPORT__
#define __WF_LS_NO_PRAGMA_SUPPORT__
#elif defined(__CLION_IDE__)
#define __WF_LS_NO_DEFINE_SUPPORT__
#define __WF_LS_NO_PRAGMA_SUPPORT__
#elif defined(__INTELLISENSE__)
#define __WF_LS_NO_PRAGMA_SUPPORT__
#endif

/* Provide (some) missing defines for language servers. */
#ifdef __WF_LS_NO_DEFINE_SUPPORT__

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

#endif

/* Provide missing pragmas for language servers. */
#ifdef __WF_LS_NO_PRAGMA_SUPPORT__

/* Pragmas. */
#define __far
#define __seg_ss
#define __seg_cs
#define __segment uint16_t

/* Built-in functions. */
#define __builtin_ia16_FP_OFF(v) ((size_t) (v))
#define __builtin_ia16_static_far_cast(p) (p)
#define __builtin_ia16_near_data_segment() 0
#define __builtin_ia16_ss() 0

#endif
