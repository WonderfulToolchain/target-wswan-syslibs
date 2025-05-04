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

#ifndef _STDBIT_H_
#define _STDBIT_H_

#define __STDC_ENDIAN_BIG__ __ORDER_BIG_ENDIAN__
#define __STDC_ENDIAN_LITTLE__ __ORDER_LITTLE_ENDIAN__
#define __STDC_ENDIAN_NATIVE__ __BYTE_ORDER__

#define stdc_leading_zeros_uc(value) __builtin_clz((unsigned char) (value))
#define stdc_leading_zeros_us(value) __builtin_clz((unsigned short) (value))
#define stdc_leading_zeros_ui(value) __builtin_clz((unsigned int) (value))
#define stdc_leading_zeros_ul(value) __builtin_clzl((unsigned long) (value))
#define stdc_leading_zeros_ull(value) __builtin_clzll((unsigned long long) (value))
#define stdc_trailing_zeros_us(value) __builtin_ctz((unsigned short) (value))
#define stdc_trailing_zeros_ui(value) __builtin_ctz((unsigned int) (value))
#define stdc_trailing_zeros_ul(value) __builtin_ctzl((unsigned long) (value))
#define stdc_trailing_zeros_ull(value) __builtin_ctzll((unsigned long long) (value))
#define stdc_leading_ones_us(value) __builtin_clz(~((unsigned short) (value)))
#define stdc_leading_ones_ui(value) __builtin_clz(~((unsigned int) (value)))
#define stdc_leading_ones_ul(value) __builtin_clzl(~((unsigned long) (value)))
#define stdc_leading_ones_ull(value) __builtin_clzll(~((unsigned long logn) (value)))
#define stdc_trailing_ones_us(value) __builtin_ctz(~((unsigned short) (value)))
#define stdc_trailing_ones_ui(value) __builtin_ctz(~((unsigned int) (value)))
#define stdc_trailing_ones_ul(value) __builtin_ctzl(~((unsigned long) (value)))
#define stdc_trailing_ones_ull(value) __builtin_ctzll(~((unsigned long) (value)))
#define stdc_first_trailing_one_uc(value) __builtin_ffs((unsigned char) (value))
#define stdc_first_trailing_one_us(value) __builtin_ffs((unsigned short) (value))
#define stdc_first_trailing_one_ui(value) __builtin_ffs((unsigned int) (value))
#define stdc_first_trailing_one_ul(value) __builtin_ffsl((unsigned long) (value))
#define stdc_first_trailing_one_ull(value) __builtin_ffsll((unsigned long long) (value))
#define stdc_count_ones_us(value) __builtin_popcount((unsigned short) (value))
#define stdc_count_ones_ui(value) __builtin_popcount((unsigned int) (value))
#define stdc_count_ones_ul(value) __builtin_popcountl((unsigned long) (value))
#define stdc_count_ones_ull(value) __builtin_popcountll((unsigned long long) (value))
#define stdc_count_zeros_us(value) __builtin_popcount(~((unsigned short) (value)))
#define stdc_count_zeros_ui(value) __builtin_popcount(~((unsigned int) (value)))
#define stdc_count_zeros_ul(value) __builtin_popcountl(~((unsigned long) (value)))
#define stdc_count_zeros_ull(value) __builtin_popcountll~((unsigned long long) (value)))

#endif /* _STDBIT_H_ */
