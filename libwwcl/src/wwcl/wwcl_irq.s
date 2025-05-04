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

    // AL = IRQ to acknowledge
    // BX = IRQ offset
    // assumes AX, BX preserved
irq_wrap_routine:
    push ax
    mov ax, ss:[bx]
    or ax, ss:[bx + 2]
    jz irq_wrap_routine_not_found

    push cx
    push dx
    push si
    push di
    push bp
    push ds
    push es

    mov ax, ss:[bx + 4]
    mov ds, ax
    ss lcall [bx]
    
    pop es
    pop ds
    pop bp
    pop di
    pop si
    pop dx
    pop cx
irq_wrap_routine_not_found:
    // Acknowledge interrupt
    pop ax
    out IO_HWINT_ACK, al
    ret

.macro irq_default_handler irq,idx
    push ax
    push bx
    mov al, \irq
    mov bx, offset (__wwcl_irq_hook + (\idx * 8))
    call irq_wrap_routine
    pop bx
    pop ax
    iret
.endm

    .global __wwcl_init_irqs
__wwcl_init_irqs:
    mov bx, sp
    mov sp, 0x0040
    push cs
    push offset __wwcl_irq_hblank_timer
    push cs
    push offset __wwcl_irq_vblank
    push cs
    push offset __wwcl_irq_vblank_timer
    push cs
    push offset __wwcl_irq_line
    push cs
    push offset __wwcl_irq_serial_rx
    push cs
    push offset __wwcl_irq_cartridge
    push cs
    push offset __wwcl_irq_key
    push cs
    push offset __wwcl_irq_serial_tx
    mov sp, bx

    mov al, 0xFF
    out IO_HWINT_ACK, al
    mov al, 0x40
    out IO_HWINT_ENABLE, al
    sti
    IA16_RET

    .global __wwcl_irq_serial_tx
__wwcl_irq_serial_tx:
    irq_default_handler HWINT_SERIAL_TX,HWINT_IDX_SERIAL_TX

    .global __wwcl_irq_key
__wwcl_irq_key:
    irq_default_handler HWINT_KEY,HWINT_IDX_KEY

    .global __wwcl_irq_cartridge
__wwcl_irq_cartridge:
    irq_default_handler HWINT_CARTRIDGE,HWINT_IDX_CARTRIDGE

    .global __wwcl_irq_serial_rx
__wwcl_irq_serial_rx:
    irq_default_handler HWINT_SERIAL_RX,HWINT_IDX_SERIAL_RX

    .global __wwcl_irq_line
__wwcl_irq_line:
    irq_default_handler HWINT_LINE,HWINT_IDX_LINE

    .global __wwcl_irq_vblank_timer
__wwcl_irq_vblank_timer:
    irq_default_handler HWINT_VBLANK_TIMER,HWINT_IDX_VBLANK_TIMER

    .global __wwcl_irq_hblank_timer
__wwcl_irq_hblank_timer:
    irq_default_handler HWINT_HBLANK_TIMER,HWINT_IDX_HBLANK_TIMER

    .global __wwcl_irq_vblank
__wwcl_irq_vblank:
    push ax
    push bx
    push cx
    push ds
    push ss
    pop ds

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

    mov al, HWINT_VBLANK
    mov bx, offset (__wwcl_irq_hook + (HWINT_IDX_VBLANK * 8))
    call irq_wrap_routine

    pop ds
    pop cx
    pop bx
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
