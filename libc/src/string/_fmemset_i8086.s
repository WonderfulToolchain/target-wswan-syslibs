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

#include "wonderful.h"

	.arch	i8086
	.code16
	.intel_syntax noprefix

	.global _fmemset
_fmemset:
#ifdef __IA16_CMODEL_IS_FAR_DATA
	.global memset
memset:
#endif
	push	di
	push	es
	push	ax
	mov	bx, sp
	mov	es, dx
	mov	di, ax
	mov	al, cl
	mov	ah, al
	ss mov	cx, [bx + IA16_CALL_STACK_OFFSET(6)]
	shr	cx, 1
	cld
	rep	stosw
	jnc	_fmemset_no_byte
	stosb
_fmemset_no_byte:
	pop	ax
	pop	es
	pop	di
	IA16_RET 0x2
