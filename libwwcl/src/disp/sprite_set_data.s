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
#include <ws.h>
#include "asm-preamble.h"
	.intel_syntax noprefix

    .global sprite_set_data
sprite_set_data:
    push bp
    mov bp, sp
    push si
    push di
    push es

    // ES:DI = destination
    push ss
    pop es
    call __wwcl_int_ax_display_sprite_to_vram_location

    // DS:SI = source
    lds si, [bp + WF_PLATFORM_CALL_STACK_OFFSET(2)]

    // CX = (sprites * 4) >> 1
    mov cx, dx
    add cx, dx

    cld
    rep movsw

    pop es
    pop di
    pop si
    pop bp
    WF_PLATFORM_RET
