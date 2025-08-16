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

#ifndef _ASSERT_H_
#define _ASSERT_H_

// TODO: Store assert() strings in ROM.

#undef assert
#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(expression) ((expression) ? (void) 0 : _assert(#expression, __FILE__, __LINE__, __FUNCTION__))
#endif

__attribute__((noreturn))
void _assert(const char *expression, const char *file, unsigned int line, const char *function);

#if __STDC_VERSION__ >= 201112L
# undef static_assert
# define static_assert _Static_assert
#endif

#endif /* _ASSERT_H_ */
