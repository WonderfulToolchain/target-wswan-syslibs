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

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include "stdlib.h"

int atoi(const char __far* str) {
	int result = 0;
	bool sign = false;

	while (isspace(*str)) { str++; }

	if (*str == '+') { str++; }
	else if (*str == '-') { sign = true; str++; }

	while (*str >= '0' && *str <= '9') {
		result = (result * 10) + (*(str++) - '0');
	}
	return sign ? -result : result;
}
