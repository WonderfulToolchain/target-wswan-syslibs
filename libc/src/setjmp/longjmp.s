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

	.global longjmp
longjmp:
#ifdef __IA16_CMODEL_IS_FAR_DATA
	// jmp_buf (DX:AX) => DS:BX
	// return value (CX) => AX
	mov bx, ax
	mov ds, dx
	mov ax, cx
#else
	mov bx, ax
	mov ax, dx
#endif

	// restore registers
	mov si, [bx+0]
	mov di, [bx+2]
	mov bp, [bx+4]
	mov es, [bx+8]
	mov ss, [bx+10]
	mov sp, [bx+12]

#ifdef __IA16_CMODEL_IS_FAR_TEXT
	push [bx+16]
#endif
	push [bx+14]

	mov ds, [bx+6]

	IA16_RET
