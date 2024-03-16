/**
 * Copyright (c) 2023, 2024 Adrian "asie" Siekierka
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
#include <ws.h>
#include "asm-preamble.h"
	.intel_syntax noprefix

	.global key_press_check
key_press_check:
    WF_PLATFORM_CALL ws_keypad_scan
    mov [__wwcl_key_last_pressed], ax
    WF_PLATFORM_RET

    .global key_hit_check
key_hit_check:
    mov bx, [__wwcl_key_last_pressed]
    WF_PLATFORM_CALL ws_keypad_scan
    mov [__wwcl_key_last_pressed], ax
    not bx
    and ax, bx
    WF_PLATFORM_RET

    .global key_wait
key_wait:
    WF_PLATFORM_CALL ws_keypad_scan
    test ax, ax
    jnz key_wait_done
    hlt
    nop
    jmp key_wait
key_wait_done:
    mov [__wwcl_key_last_pressed], ax
    WF_PLATFORM_RET

	.section .bss
	.global __wwcl_key_last_pressed
__wwcl_key_last_pressed:
    .short 0
