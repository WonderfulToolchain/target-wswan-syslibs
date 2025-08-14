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

	.arch	i186
	.code16
	.intel_syntax noprefix

	.global setjmp
setjmp:
	// jmp_buf (DX:AX) => DS:BX
	// DS => AX
	mov bx, ax
	mov ax, ds
	mov ds, dx

	// store registers in jmp_buf
	mov [bx+0], si
	mov [bx+2], di
	mov [bx+4], bp
	mov [bx+6], ds
	mov [bx+8], es
	mov [bx+10], ss

	// store return address
	pop ax
	mov [bx+14], ax
#ifdef __IA16_CMODEL_IS_FAR_TEXT
	pop dx
	mov word ptr [bx+16], dx
#endif
	mov [bx+12], sp
#ifdef __IA16_CMODEL_IS_FAR_TEXT
	push dx
#endif
	push ax

	// return (AX) => 0
	xor ax, ax

9:
	IA16_RET
