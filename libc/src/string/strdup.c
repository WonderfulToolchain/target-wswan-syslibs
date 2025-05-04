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
#include "stdlib.h"
#include "string.h"

char *strdup(const char __far* s) {
    size_t size = strlen(s) + 1;
    char *result = malloc(size);
    if (result)
        memcpy(result, s, size);
    return result;
}
