/**
 * wonderful ia16 libc
 *
 * To the extent possible under law, the person who associated CC0 with
 * wonderful ia16 libc has waived all copyright and related or neighboring rights
 * to wonderful ia16 libc.
 *
 * You should have received a copy of the CC0 legalcode along with this
 * work.  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include <stdbool.h>
#include <stddef.h>
#include "stdio.h"
#include "nanoprintf.h"

int vprintf(const char __far* format, va_list val) {
    // HACK: This takes advantage of the fact that under the -mregparmcall
    // convention, npf_putc only ever uses AX/DX/CX to pass arguments.
    return npf_vpprintf((npf_putc) putchar, NULL, format, val);
}