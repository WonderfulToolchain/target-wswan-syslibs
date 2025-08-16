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

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <wonderful.h>
#include "ws/memory.h"
#include "ws/uart.h"

int _stdin_uart_getc(FILE *stream) {
    if (!ws_uart_is_opened())
        return -1;
    return ws_uart_getc();
}

int _stdin_uart_putc(uint8_t c, FILE *stream) {
    if (!ws_uart_is_opened())
        return -1;
    ws_uart_putc(c);
    return 0;
}

const struct wf_fileops_t ws_rom _libws_uart_stdin_ops = {
    _stdin_uart_getc,
    NULL
};

const struct wf_fileops_t ws_rom _libws_uart_stdout_ops = {
    NULL,
    _stdin_uart_putc
};