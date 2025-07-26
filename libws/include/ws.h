/*
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

#ifndef LIBWS_WS_H_
#define LIBWS_WS_H_

#include <wonderful.h>
#include <ws/ports.h>
#include <ws/keypad.h>
#include <ws/eeprom.h>
#include <ws/system.h>
#include <ws/memory.h>
#include <ws/util.h>
#include <ws/display.h>
#include <ws/sound.h>
#include <ws/timer.h>
#include <ws/cart/gpio.h>
#include <ws/cart/rtc.h>

#ifndef __ASSEMBLER__
#include <ws/dma.h>
#include <ws/uart.h>
#include <ws/ext/wg.h>
#endif

#if defined(LIBWS_API_COMPAT) && LIBWS_API_COMPAT < 202505L
# include <ws/hardware.h>
# include <ws/legacy.h>
# ifndef __ASSEMBLER__
#  include <ws/serial.h>
# endif
#endif

#endif /* LIBWS_WS_H_ */
