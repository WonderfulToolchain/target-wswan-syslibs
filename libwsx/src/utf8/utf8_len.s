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

    .section .fartext.s.wsx_utf8_len, "ax"
    .global wsx_utf8_len
wsx_utf8_len:
    push ds
    push si

    xor cx, cx
    
    // DS:SI = far pointer to string
    mov si, ax
    mov ds, dx

    xor bx, bx
1:
    add si, bx
    mov al, [si]

    // if 0, finish searching
    test al, al
    jz 9f

    inc cx
    // assume 4 bytes, then 3, then 2, then 1
    mov bx, 4
    cmp al, 0xF0
    jae 1b
    dec bx
    cmp al, 0xE0
    jae 1b
    dec bx
    cmp al, 0xC0
    jae 1b
    dec bx
    cmp al, 0x80
    jb 1b

    // invalid byte
    mov cx, 0xFFFF
9:
    mov ax, cx
    pop si
    pop ds

    IA16_RET