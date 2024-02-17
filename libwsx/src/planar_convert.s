/**
 * Copyright (c) 2024 Adrian "asie" Siekierka
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
#include "asm-preamble.h"
    .intel_syntax noprefix

__wsx_planar_convert_4bpp_packed_row_table:
#include "c2p_4bpp_table.inc"

    // uint32_t wsx_planar_convert_4bpp_packed_row(uint32_t v)
    // DX:BX => CX:AX
    .global wsx_planar_convert_4bpp_packed_row
wsx_planar_convert_4bpp_packed_row:
    push bp
    push ds
    push cs
    pop ds
    mov bp, 4
    mov bx, ax
    xor ax, ax
    mov cx, ax
    jmp __wsx_planar_convert_4bpp_packed_row_loop_start
__wsx_planar_convert_4bpp_packed_row_loop:
    shl cx, 1
    shl ax, 1
    shl cx, 1
    shl ax, 1
__wsx_planar_convert_4bpp_packed_row_loop_start:
    push bx
    mov bh, 0
    shl bx, 1
    shl bx, 1
    or ax, [bx+__wsx_planar_convert_4bpp_packed_row_table]
    or cx, [bx+__wsx_planar_convert_4bpp_packed_row_table+2]
    pop bx
    dec bp
    jz __wsx_planar_convert_4bpp_packed_row_done
    mov bl, bh
    mov bh, dl
    mov dl, dh
    jmp __wsx_planar_convert_4bpp_packed_row_loop
__wsx_planar_convert_4bpp_packed_row_done:
    pop ds
    pop bp
    mov dx, cx
    WF_PLATFORM_RET

