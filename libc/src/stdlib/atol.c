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
#include <stdbool.h>
#include <stddef.h>
#include "stdlib.h"

long atol(const char __far* str) {
	long result = 0;
	bool sign = false;

	while (isspace(*str)) { str++; }

	if (*str == '+') { str++; }
	else if (*str == '-') { sign = true; str++; }

	while (*str >= '0' && *str <= '9') {
		result = (result * 10) + (*(str++));
	}
	return sign ? -result : result;
}
