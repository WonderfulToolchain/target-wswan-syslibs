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

	.global _nmemmove
_nmemmove:
#ifndef __IA16_CMODEL_IS_FAR_DATA
	.global memmove
memmove:
#endif
	push	si
	push	di
	push	es
	mov	di, ax
	mov	si, dx
	mov	bx, ds
	mov	es, bx
	cmp	ax, dx
	ja	_nmemmove_reversed	
	shr	cx, 1
	cld
	rep	movsw
	jnc	_nmemmove_no_byte
	movsb
_nmemmove_no_byte:
	pop	es
	pop	di
	pop	si
	IA16_RET

_nmemmove_reversed:
	// TODO: use rep movsw for performance
	dec	cx
	add	si, cx
	add	di, cx
	inc	cx
	std
	rep	movsb
	pop	es
	pop	di
	pop	si
	IA16_RET
