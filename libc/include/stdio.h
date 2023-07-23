/**
 * wonderful-i8086 libc
 *
 * To the extent possible under law, the person who associated CC0 with
 * wonderful-i8086 libc has waived all copyright and related or neighboring rights
 * to wonderful-i8086 libc.
 *
 * You should have received a copy of the CC0 legalcode along with this
 * work.  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#pragma once
#include <wonderful.h>
#include <stdarg.h>
#include <stddef.h>

int sprintf(char __far* restrict s, const char __far* restrict format, ...);
int snprintf(char __far* restrict s, size_t n, const char __far* restrict format, ...);
int vsprintf(char __far* restrict s, const char __far* restrict format, va_list arg);
int vsnprintf(char __far* restrict s, size_t n, const char __far* restrict format, va_list arg);
