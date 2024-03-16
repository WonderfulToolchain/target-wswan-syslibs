/**
 * Copyright (c) 2023, 2024 Adrian "asie" Siekierka
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

#include <wonderful.h>
#include <ws.h>
#include <sys/bios.h>

extern void __wwcl_irq_vblank(void);
extern uint32_t __wwcl_vbl_count;
extern uint8_t __wwcl_init_display_control;
extern uint8_t __wwcl_init_scr_base;
extern uint8_t __wwcl_init_spr_base;
extern uint8_t __wwcl_init_text_mode;

void __wwcl_init_irqs(void) {
    ws_hwint_set_default_handler_serial_tx();
    ws_hwint_set_default_handler_key();
    ws_hwint_set_default_handler_serial_rx();
    ws_hwint_set_default_handler_line();
    ws_hwint_set_default_handler_vblank_timer();
    ws_hwint_set_handler(HWINT_IDX_VBLANK, (ws_int_handler_t) __wwcl_irq_vblank);
    ws_hwint_set_default_handler_hblank_timer();

    ws_hwint_set(HWINT_VBLANK);
    cpu_irq_enable();
}

void wwcl_init_custom(void) {
    __wwcl_init_irqs();
}

void wwcl_init(void) {
    outportw(IO_DISPLAY_CTRL, __wwcl_init_display_control);
    outportb(IO_SCR_BASE, __wwcl_init_scr_base);
    outportb(IO_SPR_BASE, __wwcl_init_spr_base);
    text_set_mode(__wwcl_init_text_mode);
    wwcl_init_custom();
}
