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

    // input: AL = screen ID
    // output: DI = VRAM location
    // clobbers AX
    .global __wwcl_display_screen_to_vram_location
__wwcl_display_screen_to_vram_location:
    push cx

    add al, al
    add al, al
    mov cl, 11
    sub cl, al // CL = 11 (SCREEN1), 7 (SCREEN2)

    in al, IO_SCR_BASE
    shl ax, cl
    and ax, 0x7800
    mov di, ax

    pop cx
    ret

    // input: AL = screen ID, DL = X, CL = Y
    // output: DI = VRAM location
    // clobbers AX, BX, CX
    .global __wwcl_display_screen_and_topleft_to_vram_location
__wwcl_display_screen_and_topleft_to_vram_location:
    mov bl, dl
    mov bh, cl

    add al, al
    add al, al
    mov cl, 11
    sub cl, al // CL = 11 (SCREEN1), 7 (SCREEN2)

    in al, IO_SCR_BASE
    shl ax, cl
    and ax, 0x7800
    mov di, ax

    push bx
    and bx, 0x001F
    add di, bx
    add di, bx // * 2
    pop bx
    and bx, 0x1F00
    shr bx, 1
    shr bx, 1  // (bh >> 2) == ((bx >> 8) << 6)
    add di, bx

    ret

    // input: AX = sprite index
    // output: DI = VRAM location
    // clobbers AX
    .global __wwcl_int_ax_display_sprite_to_vram_location
__wwcl_int_ax_display_sprite_to_vram_location:
    add ax, ax
    add ax, ax
    mov di, ax
    in al, IO_SPR_BASE
    shl ax, 9
    and ah, 0x7E
    add di, ax
    ret

    // output: DI = VRAM location
    // clobbers AX
    .global __wwcl_display_sprite_to_vram_location
__wwcl_display_sprite_to_vram_location:
    in al, IO_SPR_BASE
    shl ax, 9
    and ah, 0x7E
    mov di, ax

    ret

    .section .data
    .global __wwcl_disp_font_color
__wwcl_disp_font_color:
    .byte 1
