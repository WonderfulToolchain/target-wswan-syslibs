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

#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <stdint.h>
#include <wonderful.h>

int brk(void *addr);
void *sbrk(intptr_t incr);

#endif /* _UNISTD_H_ */
