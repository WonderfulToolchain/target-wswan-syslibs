/**
 * Copyright (c) 2024 Adrian "asie" Siekierka
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

#include <stddef.h>
#include <string.h>
#include <wonderful.h>
#include <ws.h>
#include <sys/bios.h>

intvector_t __wwcl_irq_hook[8];

void sys_interrupt_set_hook(uint8_t id, intvector_t *new_vector, intvector_t *old_vector) {
    cpu_irq_disable();

    if (old_vector) memcpy(old_vector, &__wwcl_irq_hook[id], sizeof(intvector_t));
    memcpy(&__wwcl_irq_hook[id], new_vector, sizeof(intvector_t));

    cpu_irq_enable();
}

void sys_interrupt_reset_hook(uint8_t id, intvector_t *old_vector) {
    cpu_irq_disable();

    if (old_vector) sys_interrupt_set_hook(id, old_vector, NULL);
    else memset(&__wwcl_irq_hook[id], 0, sizeof(intvector_t));

    cpu_irq_enable();
}
