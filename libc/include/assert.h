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

#ifndef __WF_LIBC_ASSERT_H__
#define __WF_LIBC_ASSERT_H__

// TODO: Actually implement assert().

#undef assert
#define assert(ignore) ((void)0)

#if __STDC_VERSION__ >= 201112L
# undef static_assert
# define static_assert _Static_assert
#endif

#endif /* __WF_LIBC_ASSERT_H__ */
