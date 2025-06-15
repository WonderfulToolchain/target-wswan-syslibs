/*
 * Copyright (c) 2024, 2025 Adrian "asie" Siekierka
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

    .arch   i186
    .code16
    .intel_syntax noprefix

    .section .fartext.s.wsx_utf8_decode_next, "ax"
    .global wsx_utf8_decode_next
wsx_utf8_decode_next:
    push ds
    push si

    // SS:BX = pointer to far pointer to string
    // DS:SI = far pointer to string
    mov bx, ax
    ss lds si,[bx]
    xor ax, ax
    mov dx, ax

    lodsb
    cmp al, 0xF0
    jae 4f
    cmp al, 0xE0
    jae 3f
    cmp al, 0xC0
    jae 2f
    cmp al, 0x80
    jae 8f
9:
    ss mov [bx], si
    mov si, ds
    ss mov [bx + 2], si

    pop si
    pop ds

    IA16_RET

2:
    and al, 0x1F
    shl ax, 6
    mov cx, ax
    lodsb
    and ax, 0x003F
    or ax, cx
    jmp 9b

3:
    shl ax, 12
    mov cx, ax
    lodsb
    and ax, 0x003F
    shl ax, 6
    or cx, ax
    lodsb
    and ax, 0x003F
    or ax, cx
    jmp 9b

4:
    shl ax, 2
    and ax, 0x001C
    mov dx, ax
    lodsb
    and ax, 0x003F
    push ax
    shr ax, 4
    or dx, ax
    pop ax
    jmp 3b

8:
    mov al, '?'
    jmp 9b
