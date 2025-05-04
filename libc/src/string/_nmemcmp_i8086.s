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

	.global _nmemcmp
_nmemcmp:
#ifndef __IA16_CMODEL_IS_FAR_DATA
	.global memcmp
memcmp:
#endif
	push	si
	push	di
	push	es
	mov	di, ax
	mov	si, dx
	mov	dx, ds
	mov	es, dx
	
	xor ax, ax
	cld
	repe cmpsb
	je _nmemcmp_end

	// value mismatch
	dec si
	dec di
	mov al, [di]
	sub al, [si]
	cbw

_nmemcmp_end:
	pop	es
	pop	di
	pop	si
	IA16_RET
