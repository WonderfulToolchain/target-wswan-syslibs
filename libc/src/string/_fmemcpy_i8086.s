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

#include "wonderful.h"

	.arch	i8086
	.code16
	.intel_syntax noprefix

	.global _fmemcpy
_fmemcpy:
#ifdef __IA16_CMODEL_IS_FAR_DATA
	.global memcpy
memcpy:
#endif
	push	si
	push	di
	push	ds
	push	es
	push	bp
	mov	bp, sp
	mov	es, dx
	mov	di, ax
	lds	si, [bp + IA16_CALL_STACK_OFFSET(10)]
	mov	cx, [bp + IA16_CALL_STACK_OFFSET(14)]
	shr	cx, 1
	cld
	rep	movsw
	jnc	_fmemcpy_no_byte
	movsb
_fmemcpy_no_byte:
	// dx:ax is already set to destination
	pop	bp
	pop	es
	pop	ds
	pop	di
	pop	si
	IA16_RET 0x6
