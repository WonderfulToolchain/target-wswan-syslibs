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

#ifndef _ERRNO_H_
#define _ERRNO_H_

#include <stddef.h>

extern int _errno;
#define errno (_errno)

#define ERANGE -1
#define EDOM   -2
#define EILSEQ -3
#define EINVAL -4
#define ENOMEM -5

#endif /* _ERRNO_H_ */
