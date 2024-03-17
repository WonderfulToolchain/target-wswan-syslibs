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

    .global __wwcl_irq_vblank
__wwcl_irq_vblank:
    push ax
    push cx
    push ds
    xor ax, ax
    mov ds, ax

    // Increment VBL counter
    add word ptr [__wwcl_vbl_count], 1
    adc word ptr [__wwcl_vbl_count+2], 0

    // Handle key presses
    mov al, 0x10
    out IO_KEY_SCAN, al
    daa
    in  al, IO_KEY_SCAN
    and al, 0x0F
    mov ch, al

    mov al, 0x20
    out IO_KEY_SCAN, al
    daa
    in  al, IO_KEY_SCAN
    shl al, 4
    mov cl, al

    mov al, 0x40
    out IO_KEY_SCAN, al
    daa
    in  al, IO_KEY_SCAN
    and al, 0x0F
    or  cl, al

    mov ax, word ptr [__wwcl_key_held]
    not ax
    and ax, cx
    mov word ptr [__wwcl_key_held], cx
    mov word ptr [__wwcl_key_pressed], ax

    // Acknowledge interrupt
    mov al, HWINT_VBLANK
    out IO_HWINT_ACK, al

    pop ds
    pop cx
    pop ax
    iret

    .section .bss
    .global __wwcl_vbl_count
__wwcl_vbl_count:
.short 0, 0
    .global __wwcl_key_pressed
__wwcl_key_pressed:
.short 0
    .global __wwcl_key_held
__wwcl_key_held:
.short 0
