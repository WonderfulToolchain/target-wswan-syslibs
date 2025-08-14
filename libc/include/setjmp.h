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

#ifndef _SETJMP_H_
#define _SETJMP_H_

#include <wonderful.h>
#include <stddef.h>

/* jmp_buf preserves SI, DI, BP, DS, ES, SS, SP, IP, CS? */
#ifdef __IA16_CMODEL_IS_FAR_TEXT
typedef uint16_t __far jmp_buf[9];
#else
typedef uint16_t __far jmp_buf[8];
#endif

__attribute__((noreturn)) void longjmp(jmp_buf env, int val);
int setjmp(jmp_buf env);

#endif /* _SETJMP_H_ */
