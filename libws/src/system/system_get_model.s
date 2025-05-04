/**
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

#include <wonderful.h>
#include "ws/ports.h"
#include "asm-preamble.h"
	.intel_syntax noprefix

#define WS_MODEL_MONO 0x00
#define WS_MODEL_PCV2 0x01
#define WS_MODEL_COLOR 0x82
#define WS_MODEL_CRYSTAL 0x83

	.global ws_system_get_model
ws_system_get_model:
    xor ax, ax
    
    in al, WS_SYSTEM_CTRL_PORT
    test al, WS_SYSTEM_CTRL_COLOR
    jnz __ws_system_get_model_color

	xor al, al
	out	0xB5, al
	daa
	in	al, 0xB5
    test al, 0x02
    jnz __ws_system_get_model_pcv2

    mov al, WS_MODEL_MONO
	WF_PLATFORM_RET

__ws_system_get_model_pcv2:
    mov al, WS_MODEL_PCV2
    WF_PLATFORM_RET

__ws_system_get_model_color:
    in al, WS_SYSTEM_CTRL_COLOR2_PORT
    test al, WS_SYSTEM_CTRL_COLOR2_CRYSTAL
    jnz __ws_system_get_model_crystal
    mov al, WS_MODEL_COLOR
    WF_PLATFORM_RET

__ws_system_get_model_crystal:
    mov al, WS_MODEL_CRYSTAL
    WF_PLATFORM_RET
