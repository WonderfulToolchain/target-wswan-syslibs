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

/** \file keypad.h
 * Functionality related to the keypad.
 */

#ifndef LIBWS_KEYPAD_H_
#define LIBWS_KEYPAD_H_

/**
 * @addtogroup keypad Key input
 * @{
 */

#define WS_KEY_Y4    0x0800
#define WS_KEY_Y3    0x0400
#define WS_KEY_Y2    0x0200
#define WS_KEY_Y1    0x0100
#define WS_KEY_X4    0x0080
#define WS_KEY_X3    0x0040
#define WS_KEY_X2    0x0020
#define WS_KEY_X1    0x0010
#define WS_KEY_B     0x0008
#define WS_KEY_A     0x0004
#define WS_KEY_START 0x0002

#define WS_KEY_PCV2_PASS   0x0800
#define WS_KEY_PCV2_CIRCLE 0x0400
#define WS_KEY_PCV2_CLEAR  0x0100
#define WS_KEY_PCV2_RIGHT  0x0080
#define WS_KEY_PCV2_ESC    0x0040
#define WS_KEY_PCV2_VIEW   0x0010
#define WS_KEY_PCV2_UP     0x0008
#define WS_KEY_PCV2_DOWN   0x0004
#define WS_KEY_PCV2_LEFT   0x0001

#ifndef __ASSEMBLER__

#include <stdint.h>
 
/**
 * @brief Query the current state of the keypad.
 * 
 * @return uint16_t A bitfield representing currently pressed keys.
 */
__attribute__((no_assume_ds_data, no_assume_ss_data))
uint16_t ws_keypad_scan(void);

/**@}*/

#endif /* __ASSEMBLER__ */

#endif /* LIBWS_KEYPAD_H_ */
