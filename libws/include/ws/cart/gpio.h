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

/** \file cart/gpio.h
 * Functionality related to the on-cartridge GPIO.
 */

#ifndef LIBWS_CART_GPIO_H_
#define LIBWS_CART_GPIO_H_

#include <wonderful.h>
#include "../ports.h"

/**
 * @addtogroup cart_gpio Cartridge - GPIO
 * @{
 */

#define WS_CART_GPIO_PIN(n) (1 << (n))
#define WS_CART_GPIO_PIN_0 0x01
#define WS_CART_GPIO_PIN_1 0x02
#define WS_CART_GPIO_PIN_2 0x04
#define WS_CART_GPIO_PIN_3 0x08

#ifndef __ASSEMBLER__

#include <stdbool.h>
#include <stdint.h>

void ws_cart_gpio_set_output(uint8_t mask);
void ws_cart_gpio_set_input(uint8_t mask);
void ws_cart_gpio_set(uint8_t mask);
void ws_cart_gpio_clear(uint8_t mask);

#endif

/**@}*/

#endif /* LIBWS_CART_GPIO_H_ */
