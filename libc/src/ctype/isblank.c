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
#include "ctype.h"

int isblank(int c) {
#if defined(LIBC_LOCALE_ASCII) || defined(LIBC_LOCALE_SJIS)
	return (c == ' ') || (c == '\t');
#else
# error Please define LIBC_LOCALE!
#endif
}