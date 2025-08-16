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

#include <stddef.h>
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"

static const char __wf_rom format[] = "Assertion failed: %s, function %s, file %s, line %d.\n";

__attribute__((weak))
void _assert(const char *expression, const char *file, unsigned int line, const char *function) {
    printf(format, (const char __far*) expression, (const char __far*) function, (const char __far*) file, line);
    abort();
}