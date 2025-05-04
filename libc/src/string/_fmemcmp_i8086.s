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

	.global _fmemcmp
_fmemcmp:
#ifdef __IA16_CMODEL_IS_FAR_DATA
	.global memcmp
memcmp:
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
	xor ax, ax
	cld
	repe cmpsb
	je _fmemcmp_end

	// value mismatch
	dec si
	dec di
	es mov al, [di]
	sub al, [si]
	cbw

_fmemcmp_end:
	pop	bp
	pop	es
	pop	ds
	pop	di
	pop	si
	IA16_RET 0x6
