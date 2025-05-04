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

	.global strlen
strlen:
	push	di
	push	es
	mov	di, ax
	mov	es, dx
	
	xor ax, ax
	mov cx, 0xFFFF
	cld
	repne scasb

	inc cx
	inc cx
	sub ax, cx

	pop	es
	pop	di
	IA16_RET
