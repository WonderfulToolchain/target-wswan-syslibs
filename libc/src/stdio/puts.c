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

int puts(const char __far* s) {
    while (*s) {
        int result = putchar(*(s++));
        if (result < 0)
            return result;
    }
    return 0;
}