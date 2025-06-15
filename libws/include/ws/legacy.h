/*
 * Copyright (c) 2022 Adrian "asie" Siekierka
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

#ifndef LIBWS_LEGACY_H_
#define LIBWS_LEGACY_H_

#if defined(LIBWS_API_COMPAT) && LIBWS_API_COMPAT < 202505L

#define __WF_IRAM_TO_OFFSET(x) ((unsigned int) (x))

#define ws_dma_set_sourcei ws_gdma_set_sourcei
#define ws_dma_set_sourcep ws_gdma_set_sourcep
#define ws_dma_set_source ws_gdma_set_source
#define ws_dma_copy_words ws_gdma_copyp
#define ws_dma_copy_words_linear ws_gdma_copyi
#define ws_dma_opt_copy_words ws_gdma_maybe_copy

#define ws_system_is_color ws_system_is_color_model
#define ws_system_color_active ws_system_is_color_active
#define ws_system_mode_get ws_system_get_mode
#define ws_system_mode_set ws_system_set_mode

#define ws_mode_get ws_system_get_mode
#define ws_mode_set ws_system_set_mode

#define ws_cpuint_set_handler ia16_int_set_handler
#define ws_hwint_set_handler ws_int_set_handler
#define ws_hwint_set_default_handler_serial_tx ws_int_set_default_handler_serial_tx
#define ws_hwint_set_default_handler_key ws_int_set_default_handler_key
#define ws_hwint_set_default_handler_serial_rx ws_int_set_default_handler_serial_rx
#define ws_hwint_set_default_handler_line ws_int_set_default_handler_line
#define ws_hwint_set_default_handler_vblank_timer ws_int_set_default_handler_vblank_timer
#define ws_hwint_set_default_handler_vblank ws_int_set_default_handler_vblank
#define ws_hwint_set_default_handler_hblank_timer ws_int_set_default_handler_hblank_timer
#define ws_hwint_set ws_int_enable_set
#define ws_hwint_push ws_int_enable_push
#define ws_hwint_pop ws_int_enable_push
#define ws_hwint_disable_all ws_int_disable_all
#define ws_hwint_ack ws_int_ack
#define ws_hwint_enable ws_int_enable
#define ws_hwint_disable ws_int_disable

#define ws_busywait ws_delay_us

#define WF_PLATFORM_CALL_STACK_OFFSET IA16_CALL_STACK_OFFSET
#define WF_PLATFORM_CALL IA16_CALL
#define WF_PLATFORM_JMP IA16_JMP
#define WF_PLATFORM_RET IA16_RET

#define ASM_PLATFORM_CALL_STACK_OFFSET IA16_CALL_STACK_OFFSET
#define ASM_PLATFORM_CALL IA16_CALL
#define ASM_PLATFORM_JMP IA16_JMP
#define ASM_PLATFORM_RET IA16_RET

#define cpu_irq_disable ia16_disable_irq
#define cpu_irq_enable ia16_enable_irq
#define cpu_halt ia16_halt

#define MEM_RAM WS_IRAM_MEM
#define MEM_SRAM WS_SRAM_MEM
#define MEM_ROM0 WS_ROM0_MEM
#define MEM_ROM1 WS_ROM1_MEM
#define MEM_ROM_LINEAR ((uint8_t __far*) 0x40000000)

#define ws_bank_rom_linear_save ws_bank_roml_save
#define ws_bank_rom_linear_set ws_bank_roml_set
#define ws_bank_rom_linear_restore ws_bank_roml_restore

#define ws_ieep_protect_enable ws_ieep_set_protect
#define ws_ieep_protect_check ws_ieep_is_protected

#define WF_BANK_INDEX(x) (x)

#define DISPLAY_WIDTH WS_DISPLAY_WIDTH_TILES
#define DISPLAY_HEIGHT WS_DISPLAY_HEIGHT_TILES
#define DISPLAY_WIDTH_PX WS_DISPLAY_WIDTH_PIXELS
#define DISPLAY_HEIGHT_PX WS_DISPLAY_HEIGHT_PIXELS
#define SCR_WIDTH WS_SCREEN_WIDTH_TILES
#define SCR_HEIGHT WS_SCREEN_HEIGHT_TILES
#define SCR_WIDTH_PX WS_SCREEN_WIDTH_PIXELS
#define SCR_HEIGHT_PX WS_SCREEN_HEIGHT_PIXELS
#define TILE_WIDTH WS_DISPLAY_TILE_WIDTH
#define TILE_HEIGHT WS_DISPLAY_TILE_HEIGHT

#define SCR_ATTR_TILE(x) (x)
#define SCR_ATTR_TILE_MASK (0x1FF)
#define SCR_ATTR_PALETTE(x) ((x) << 9)
#define SCR_ATTR_PALETTE_MASK (0xF << 9)
#define SCR_ATTR_BANK(x) ((x) << 13)
#define SCR_ATTR_BANK_MASK (0x2000)
#define SCR_ATTR_TILE_EX(x) (((x) & 0x1FF) | (((x) >> 13) << 13))
#define SCR_ATTR_TILE_EX_MASK (0x21FF)
#define SCR_ATTR_TILE_BANK_MASK (SCR_ATTR_TILE_MASK | SCR_ATTR_BANK_MASK)

#define SCR_ATTR_FLIP_H    0x4000
#define SCR_ATTR_FLIP_V    0x8000
#define SCR_ATTR_FLIP      0xC000
#define SCR_ATTR_FLIP_MASK 0xC000

#define SPR_ATTR_PALETTE(x) ((x) << 9)
#define SPR_ATTR_PALETTE_MASK	(0x7 << 9)
#define SPR_ATTR_INSIDE   0x1000
#define SPR_ATTR_PRIORITY 0x2000
#define SPR_ATTR_FLIP_H   0x4000
#define SPR_ATTR_FLIP_V   0x8000

#define WS_SPRITE_MAX_COUNT 128

#define SCR_ENTRY_TILE(x) (x)
#define SCR_ENTRY_TILE_MASK (0x1FF)
#define SCR_ENTRY_PALETTE(x) ((x) << 9)
#define SCR_ENTRY_PALETTE_MASK (0xF << 9)
#define SCR_ENTRY_BANK(x) ((x) << 13)
#define SCR_ENTRY_BANK_MASK (0x2000)
#define SCR_ENTRY_TILE_EX(x) (((x) & 0x1FF) | (((x) >> 13) << 13))
#define SCR_ENTRY_TILE_EX_MASK (0x21FF)
#define SCR_ENTRY_TILE_BANK_MASK (SCR_ENTRY_TILE_MASK | SCR_ENTRY_BANK_MASK)

#define SCR_ENTRY_FLIP_H    0x4000
#define SCR_ENTRY_FLIP_V    0x8000
#define SCR_ENTRY_FLIP      0xC000
#define SCR_ENTRY_FLIP_MASK 0xC000

#define SPR_ENTRY_PALETTE(x) ((x) << 9)
#define SPR_ENTRY_PALETTE_MASK	(0x7 << 9)
#define SPR_ENTRY_INSIDE   0x1000
#define SPR_ENTRY_PRIORITY 0x2000
#define SPR_ENTRY_FLIP_H   0x4000
#define SPR_ENTRY_FLIP_V   0x8000

#define MEM_TILE WS_TILE_MEM
#define MEM_TILE_4BPP WS_TILE_4BPP_MEM
#define MEM_TILE_4BPP_BANK0(i) WS_TILE_4BPP_MEM(i)
#define MEM_TILE_4BPP_BANK1(i) WS_TILE_4BPP_MEM((i)+512)

#define MEM_COLOR_PALETTE WS_DISPLAY_COLOR_MEM
#define MEM_SCR_PALETTE WS_SCREEN_COLOR_MEM
#define MEM_SPR_PALETTE WS_SPRITE_COLOR_MEM

#define SHADE_LUT WS_DISPLAY_SHADE_LUT
#define SHADE_LUT_DEFAULT WS_DISPLAY_SHADE_LUT_DEFAULT
#define RGB WS_RGB

#define KEY_Y4    0x0800
#define KEY_Y3    0x0400
#define KEY_Y2    0x0200
#define KEY_Y1    0x0100
#define KEY_X4    0x0080
#define KEY_X3    0x0040
#define KEY_X2    0x0020
#define KEY_X1    0x0010
#define KEY_B     0x0008
#define KEY_A     0x0004
#define KEY_START 0x0002

#define KEY_PCV2_PASS   0x0800
#define KEY_PCV2_CIRCLE 0x0400
#define KEY_PCV2_CLEAR  0x0100
#define KEY_PCV2_RIGHT  0x0080
#define KEY_PCV2_ESC    0x0040
#define KEY_PCV2_VIEW   0x0010
#define KEY_PCV2_UP     0x0008
#define KEY_PCV2_DOWN   0x0004
#define KEY_PCV2_LEFT   0x0001

#endif

#endif /* LIBWS_LEGACY_H_ */
