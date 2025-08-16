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

    .section .data.stdin, "a"
    .global stdin
_stdin:
    .word 0, 0
    .word _libws_uart_stdin_ops
	.reloc ., R_386_SEG16, "_libws_uart_stdin_ops!"
    .word 0
stdin:
    .word _stdin

    .section .data._stdout, "a"
_stdout:
    .word 0, 0
    .word _libws_uart_stdout_ops
	.reloc ., R_386_SEG16, "_libws_uart_stdout_ops!"
    .word 0

    .section .data.stdout, "a"
    .global stdout
stdout:
    .word _stdout

    .section .data.stderr, "a"
    .global stderr
stderr:
    .word _stdout