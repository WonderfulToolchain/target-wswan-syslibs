/**
 * Copyright (c) 2025 Adrian "asie" Siekierka
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

	.global ws_display_scroll_screen_by
ws_display_scroll_screen_by:
    // BL = X, CL = Y
    mov bx, dx
    // DX = port (0x10 or 0x12)
    shl al, 1
    add al, WS_SCR1_SCRL_X_PORT
    xor dx, dx
    mov dl, al
    
    in ax, dx
    add al, bl
    add ah, cl
    out dx, ax
	
    IA16_RET
