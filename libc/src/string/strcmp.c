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
#include "string.h"

int strcmp(const char __far* s1, const char __far* s2) {
	while ((*s1) && (*s1 == *s2)) {
		s1++;
		s2++;
	}
	return ((unsigned char) (*s1)) - ((unsigned char) (*s2));
}
