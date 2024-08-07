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

#include <ctype.h>
#include <stddef.h>
#include "string.h"

int strcasecmp(const char __far* s1, const char __far* s2) {
	int result = 0;
	while ((*s1) && !(result = (toupper((unsigned char) *s1) - toupper((unsigned char) *s2)))) {
		s1++;
		s2++;
	}
	return result;
}
