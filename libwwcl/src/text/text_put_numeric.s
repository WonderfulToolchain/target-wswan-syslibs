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

// Scary...

#define NUM_HEXA        0x01
#define NUM_PADSPACE    0x00
#define NUM_PADZERO     0x02
#define NUM_ALIGN_RIGHT 0x00
#define NUM_ALIGN_LEFT  0x04
#define NUM_SIGNED      0x08

text_num_table:
    .byte '0', '1', '2', '3', '4', '5', '6' ,'7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'

text_num_put_char_or_memory:
    test ax, ax // character == 0?
    jz .return

.wrap_put_char:
    push ax
    push bx    
    push cx
    push dx
    mov cx, ax
    mov al, bl
    mov dl, bh
    IA16_CALL text_put_char
    pop dx
    pop cx
    pop bx
    pop ax
    inc bl
.return:
    ret

text_num_put_signed:
    push ax
    mov ax, '-'
    call .wrap_put_char
    pop ax
    ret

    .global text_put_numeric
text_put_numeric:
    push di
    push bp
    mov bp, sp

    mov bl, al // BL = X
    mov bh, dl // BH = Y
    mov ch, [bp + IA16_CALL_STACK_OFFSET(4)] // CH = flags
    // CL = width
    mov ax, [bp + IA16_CALL_STACK_OFFSET(6)] // AX = number

    // allocate string buffer
    // BP = pointer
    mov di, bp // DI = end
    sub sp, 8

    test ch, NUM_SIGNED
    jz .no_signed
    // if signed, clear if number not signed
    test ah, 0x80
    jz .not_signed
    // convert to unsigned - we'll re-add the sign later
    neg ax
    jmp .no_signed
.not_signed:
    and ch, ~NUM_SIGNED
.no_signed:

    // convert to string
    push bx

.loop:
    test ch, NUM_HEXA
    jz .div_deca
    mov dx, ax
    and dx, 0x000F
    shr ax, 4
    jmp .div_end
.div_deca:
    xor dx, dx
    mov bx, 10
    div bx
    // DX = number % n
    // AX = number / n
.div_end:
    mov bx, dx
    dec bp
    mov dl, cs:[text_num_table + bx]
    mov [bp], dl

    test ax, ax
    jnz .loop

    pop bx
    // end convert to string

    sub di, bp
    mov dx, di // DX = actual string length, BP = string start

    xor ax, ax // AX (pushed) = written byte count

    // handle alignment
    test cl, cl // is length provided?
    jz .align_end
    push cx
    test ch, NUM_ALIGN_LEFT // no alignment if left-aligned
    jnz .align_put_signed

    sub cl, dl

    test ch, NUM_PADZERO
    jnz .align_padzero
    test ch, NUM_SIGNED
    mov ch, ' '             // pad with spaces - sign comes last
    jz .align_pad
    dec cl
    jmp .align_pad

.align_padzero:
    test ch, NUM_SIGNED
    jz .align_padzero_unsigned
    call text_num_put_signed    // pad with zeroes - sign comes first
    dec cl
.align_padzero_unsigned:
    mov ch, '0'
.align_pad:
    push ax
    mov al, ch      // AH is already clear
    call text_num_put_char_or_memory
    pop ax
    dec cl
    jnz .align_pad

.align_put_signed:
    cmp ch, '0'
    pop cx
    je .align_end // pad with zeroes - sign comes first
    test ch, NUM_SIGNED
    jz .align_end
    call text_num_put_signed

.align_end:
    mov cx, dx
    add ax, dx
    push ax
.write_number_loop:
    xor ax, ax
    mov al, [bp]
    call text_num_put_char_or_memory
    inc bp
    loop .write_number_loop

    xor ax, ax
    call text_num_put_char_or_memory
    pop ax

    add sp, 8

    pop bp
    pop di
    IA16_RET 0x4
