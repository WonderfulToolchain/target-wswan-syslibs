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

#define MEM_RAM WS_IRAM
#define MEM_SRAM WS_SRAM
#define MEM_ROM0 WS_ROM0
#define MEM_ROM1 WS_ROM1
#define MEM_ROM_LINEAR ((uint8_t __far*) 0x40000000)

#define ws_bank_rom_linear_save ws_bank_roml_save
#define ws_bank_rom_linear_set ws_bank_roml_set
#define ws_bank_rom_linear_restore ws_bank_roml_restore

#define ws_ieep_protect_enable ws_ieep_set_protect
#define ws_ieep_protect_check ws_ieep_is_protected

#endif

#endif /* LIBWS_LEGACY_H_ */
