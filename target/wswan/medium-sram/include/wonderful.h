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

#ifndef __WF_WONDERFUL_H__
#define __WF_WONDERFUL_H__

#include "../../wonderful-common-pre.h"

#define __WONDERFUL_WSWAN__
#define __wf_rom __far
#define __wf_iram __seg_ss
#define __wf_sram

#ifdef __WF_LS_NO_DEFINE_SUPPORT__
/* See wonderful-common.h for rationale. */
#define __IA16_CMODEL_MEDIUM__
#define __IA16_CMODEL_IS_FAR_TEXT
#define __IA16_ABI_SEGELF
#define __IA16_CALLCVT_REGPARMCALL
#define __IA16_CALLCVT_NO_ASSUME_SS_DATA
#endif

#include "../../wonderful-common.h"

#endif /* __WF_WONDERFUL_H__ */
