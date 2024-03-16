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

/** \file sys/text.h
 * FreyaBIOS text calls.
 */

#ifndef __WF_LIBWW_TEXT_H__
#define __WF_LIBWW_TEXT_H__

#include "types.h"

/**
 * @addtogroup Int13 BIOS - INT 13h - Text
 * @{
 */

#define TEXT_SCREEN_WIDTH  28
#define TEXT_SCREEN_HEIGHT 18

void text_screen_init(void);
void text_window_init(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t base);

#define TEXT_MODE_ANK      0
#define TEXT_MODE_ANK_SJIS 1
#define TEXT_MODE_SJIS     2

void text_set_mode(uint16_t mode);
uint16_t text_get_mode(void);
uint16_t text_put_char(uint8_t x, uint8_t y, uint16_t chr);
uint16_t text_put_string(uint8_t x, uint8_t y, const char __far* str);
uint16_t text_put_substring(uint8_t x, uint8_t y, const char __far* str, uint16_t length);

#define NUM_HEXA        0x01
#define NUM_PADSPACE    0x00
#define NUM_PADZERO     0x02
#define NUM_ALIGN_RIGHT 0x00
#define NUM_ALIGN_LEFT  0x04
#define NUM_SIGNED      0x08
#define NUM_STORE       0x80

uint16_t text_put_numeric(uint8_t x, uint8_t y, uint8_t width, uint8_t flags, uint16_t value);
uint16_t text_fill_char(uint8_t x, uint8_t y, uint16_t length, uint16_t chr);
void text_set_palette(uint16_t palette_index);
uint16_t text_get_palette(void);
void text_get_fontdata(uint16_t chr, void __far* buf);
void text_set_screen(uint8_t screen_id);
uint16_t text_get_screen(void);
void cursor_display(uint8_t on);
uint16_t cursor_status(void);
void cursor_set_location(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
uint32_t cursor_get_location(void);
void cursor_set_type(uint16_t palette_index, uint16_t blink_interval);
uint32_t cursor_get_type(void);

/**@}*/

#endif /* __WF_LIBWW_TEXT_H__ */
