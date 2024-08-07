/**
 * Copyright (c) 2022, 2023 Adrian "asie" Siekierka
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
*/

	.arch	i8086
	.code16
	.intel_syntax noprefix

#define DCM_SCR1 0x0001
#define DCM_SCR2 0x0002
#define DCM_SPR  0x0004

#define TEXT_MODE_ANK      0
#define TEXT_MODE_ANK_SJIS 1
#define TEXT_MODE_SJIS     2

#if defined(DISPLAY_MODE_JAPANESE2)
# define DISPLAY_CONTROL_VAL (DCM_SCR1 | DCM_SCR2)
# define SCR1_ADDR 0x1000
# define SCR2_ADDR 0x1800
# define SPR_ADDR 0xe00
# define STACK_ADDR 0xe00
# define TEXT_MODE TEXT_MODE_ANK_SJIS
#elif defined(DISPLAY_MODE_JAPANESE1)
# define DISPLAY_CONTROL_VAL (DCM_SCR2)
# define SCR1_ADDR 0x1800
# define SCR2_ADDR 0x1800
# define SPR_ADDR 0x1600
# define STACK_ADDR 0x1600
# define TEXT_MODE TEXT_MODE_ANK_SJIS
#elif defined(DISPLAY_MODE_ASCII2)
# define DISPLAY_CONTROL_VAL (DCM_SCR1 | DCM_SCR2)
# define SCR1_ADDR 0x3000
# define SCR2_ADDR 0x2800
# define SPR_ADDR 0x2600
# define STACK_ADDR 0x2600
# define TEXT_MODE TEXT_MODE_ANK
#elif defined(DISPLAY_MODE_ASCII1)
# define DISPLAY_CONTROL_VAL (DCM_SCR2)
# define SCR1_ADDR 0x3000
# define SCR2_ADDR 0x3000
# define SPR_ADDR 0x2e00
# define STACK_ADDR 0x2e00
# define TEXT_MODE TEXT_MODE_ANK
#else
# error Must specify DISPLAY_MODE!
#endif

	.section .start, "ax"
	.global _start
_start:
	push	ds
	push	si
	push	di
	push	cx

	xor	si, si
	xor	di, di
	mov	ax, 0x1000 // data offset
	mov	es, ax
	mov	ax, cs
	mov	dx, ax

	.reloc	.+1, R_386_SEG16, "__erom!"
	// add ax, 0
	.byte 0x05, 0x00, 0x00

	mov	ds, ax
	mov	cx, offset "__lwdata"
	cld
	rep	movsw
	mov	cx, offset "__lwbss"
	xor	ax, ax
	rep	stosw

	mov	[es:0x58], di // end of program data
	mov	[es:0x5e], di // TODO: end of program data?

	mov	ax, offset "_premain"

	pop	cx
	pop	di
	pop	si
	pop	ds
	retf

_premain:
	mov	bp, sp

	// hardware initialization
	// 1. disable display_control
	xor	ax, ax
	xor	bx, bx
	xor	cx, cx
	int	0x12
	// 2. disable SCR2 and SPR window
	mov	ax, 0x1500
	int	0x12
	mov	ax, 0x1700
	int	0x12
	// 3. disable sprites
	mov	ax, 0x0b00
	int 0x12
	// 4. reset scroll on SCR1, SCR2
	mov	ax, 0x1300
	int	0x12
	mov	ax, 0x1301
	int	0x12
	// 5. initialize SCR1, SCR2, SPR VRAM locations
	mov	ax, 0x2100
	mov	bl, (SCR1_ADDR >> 11)
	int	0x12
	mov	ax, 0x2101
	mov	bl, (SCR2_ADDR >> 11)
	int	0x12
	mov	ah, 0x22
	mov	bl, (SPR_ADDR >> 9)
	int	0x12
	// 6. initialize text mode
	mov	ah, 0x02
	mov	bl, TEXT_MODE
	int	0x13
	mov	ax, 0x0e01
	int	0x13
	// 7. enable display_control
	xor	ax, ax
	mov	bl, (DISPLAY_CONTROL_VAL)
	int	0x12

	// configure ds to point to sram
	// (reusing al = 0x00 from step 7)
	mov	ax, 0x1000
	mov	ds, ax
	mov	es, ax

	// configure ss to point to iram
	mov	ax, (STACK_ADDR)
	mov	sp, ax

	// pass argc/argv
	mov	ax, word ptr [bp + 0x8]
	mov	dx, word ptr [bp + 0x6]
	call	main

	// exit to FreyaBIOS
	int	0x10
	retf

	// process control block
	.section .data_pcb
	.global ww_pcb
ww_pcb:
	.byte	'G', 'C', 'C', 0 // compiler ID
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0, 0 // ILibIL structure pointer
	.word 0, 0 // ProcIL structure pointer
	.word 0, 0
	.fill	0x40, 1, 0x00 // current working directory
	.word 0 // argv pointer
	.word 0, 0
	.word 0
