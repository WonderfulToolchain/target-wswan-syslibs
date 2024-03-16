/**
 * Copyright (c) 2022, 2024 Adrian "asie" Siekierka
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

    .global font_set_monodata
font_set_monodata:
    push bp
    mov bp, sp
    push ds
    push es
    push si
    push di

    // DS:SI = source
    lds si, [bp + WF_PLATFORM_CALL_STACK_OFFSET(2)]

    // ES:DI = destination
    push ss
    pop es
    mov di, ax
    shl di, 4
    add di, 0x2000

    // CX = words
    mov cx, dx
    shl cx, 3

    // BX, DX free
    // BX = background mask
    // DX = foreground mask

    // to convert 0,1 (a) to 0,FF (A):
    // A = (a^1)-1
    // TODO: this might be faster, smaller, better as a table

    mov al, ss:[__wwcl_disp_font_color]
    not al

    mov dl, al
    and dl, 1
    dec dl
    shr al, 1

    mov dh, al
    and dh, 1
    dec dh
    shr al, 1

    mov bl, al
    and bl, 1
    dec bl
    shr al, 1

    mov bh, al
    and bh, 1
    dec bh

    cld
font_set_monodata_loop:
    lodsb
    mov ah, al
    push dx
    and dx, ax
    not ax
    and ax, bx
    or ax, dx
    pop dx
    stosw
    loop font_set_monodata_loop

    pop di
    pop si
    pop es
    pop ds
    pop bp
    ret
