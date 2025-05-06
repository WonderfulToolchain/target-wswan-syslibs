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

#ifndef LIBWS_DISPLAY_H_
#define LIBWS_DISPLAY_H_

#include <stdbool.h>
#include <stdint.h>
#include <wonderful.h>
#include "memory.h"

/** \file display.h
 * Functionality related to the display.
 */

/**
 * @addtogroup display Display
 * @{
 */

#define WS_DISPLAY_WIDTH_TILES   28
#define WS_DISPLAY_HEIGHT_TILES  18
#define WS_DISPLAY_WIDTH_PIXELS  (WS_DISPLAY_WIDTH_TILES  * WS_DISPLAY_TILE_WIDTH)
#define WS_DISPLAY_HEIGHT_PIXELS (WS_DISPLAY_HEIGHT_TILES * WS_DISPLAY_TILE_HEIGHT)

#define WS_DISPLAY_TILE_WIDTH     8
#define WS_DISPLAY_TILE_HEIGHT    8
#define WS_DISPLAY_TILE_SIZE      16
#define WS_DISPLAY_TILE_SIZE_4BPP 32

typedef struct {
	uint16_t row[WS_DISPLAY_TILE_HEIGHT];
} ws_display_tile_t;

typedef struct {
	uint32_t row[WS_DISPLAY_TILE_HEIGHT];
} ws_display_tile_4bpp_t;

#define WS_SCREEN_ATTR_TILE(x) (x)
#define WS_SCREEN_ATTR_TILE_MASK (0x1FF)
#define WS_SCREEN_ATTR_PALETTE(x) ((x) << 9)
#define WS_SCREEN_ATTR_PALETTE_MASK (0xF << 9)
#define WS_SCREEN_ATTR_BANK(x) ((x) << 13)
#define WS_SCREEN_ATTR_BANK_MASK (0x2000)
#define WS_SCREEN_ATTR_TILE_EX(x) (((x) & 0x1FF) | (((x) >> 13) << 13))
#define WS_SCREEN_ATTR_TILE_EX_MASK (0x21FF)
#define WS_SCREEN_ATTR_TILE_BANK_MASK (WS_SCREEN_ATTR_TILE_MASK | WS_SCREEN_ATTR_BANK_MASK)

#define WS_SCREEN_ATTR_FLIP_H    0x4000
#define WS_SCREEN_ATTR_FLIP_V    0x8000
#define WS_SCREEN_ATTR_FLIP      0xC000
#define WS_SCREEN_ATTR_FLIP_MASK 0xC000

#define WS_SCREEN_WIDTH_TILES   32
#define WS_SCREEN_HEIGHT_TILES  32
#define WS_SCREEN_WIDTH_PIXELS  (WS_SCREEN_WIDTH_TILES  * WS_DISPLAY_TILE_WIDTH)
#define WS_SCREEN_HEIGHT_PIXELS (WS_SCREEN_HEIGHT_TILES * WS_DISPLAY_TILE_HEIGHT)

typedef struct {
	uint16_t attr;
	uint8_t y;
	uint8_t x;
} ws_sprite_t;

#define WS_SPRITE_ATTR_PALETTE(x) ((x) << 9)
#define WS_SPRITE_ATTR_PALETTE_MASK	(0x7 << 9)
#define WS_SPRITE_ATTR_INSIDE    0x1000
#define WS_SPRITE_ATTR_PRIORITY  0x2000
#define WS_SPRITE_ATTR_FLIP_H    0x4000
#define WS_SPRITE_ATTR_FLIP_V    0x8000
#define WS_SPRITE_ATTR_FLIP      0xC000
#define WS_SPRITE_ATTR_FLIP_MASK 0xC000

#define WS_SPRITE_MAX_COUNT 128

/**
 * @brief Pointer to tile.
 *
 * @param i Tile index (0-1023).
 */
#define WS_TILE_MEM(i) ((ws_display_tile_t ws_iram *) (0x2000 + ((i) << 4)))

/**
 * @brief Pointer to 4bpp tile.
 *
 * @param i Tile index (0-1023).
 */
#define WS_TILE_4BPP_MEM(i) ((ws_display_tile_4bpp_t ws_iram *) (0x4000 + ((i) << 5)))

/**
 * @brief Pointer to tile, with bank specified separately.
 *
 * @param b Tile bank (0-1).
 * @param i Tile index (0-511).
 */
#define WS_TILE_BANKED_MEM(b, i) ((ws_display_tile_t ws_iram *) (0x2000 + (!!(b) << 13) + ((i) << 4)))

/**
 * @brief Pointer to 4bpp, tile, with bank specified separately.
 *
 * @param b Tile bank (0-1).
 * @param i Tile index (0-511).
 */
#define WS_TILE_4BPP_BANKED_MEM(b, i) ((ws_display_tile_4bpp_t ws_iram *) (0x4000 + (!!(b) << 14) + ((i) << 5)))

/**
 * @brief Pointer to color palette.
 *
 * @param i Color palette (0-15).
 */
#define WS_DISPLAY_COLOR_MEM(i) ((uint16_t ws_iram *) (0xFE00 + ((i) << 5)))

/**
 * @brief Pointer to screen color palette.
 *
 * @param i Color palette (0-15).
 */
#define WS_SCREEN_COLOR_MEM WS_DISPLAY_COLOR_MEM

/**
 * @brief Pointer to sprite color palette.
 *
 * @param i Color palette (0-7).
 */
#define WS_SPRITE_COLOR_MEM(i) ((uint16_t ws_iram *) (0xFF00 + ((i) << 5)))

#define WS_DISPLAY_SHADE_LUT(c0, c1, c2, c3, c4, c5, c6, c7) \
	(((uint32_t)(c0)) | (((uint32_t)(c1)) << 4) | (((uint32_t)(c2)) << 8) | (((uint32_t)(c3)) << 12) | \
	(((uint32_t)(c4)) << 16) | (((uint32_t)(c5)) << 20) | (((uint32_t)(c6)) << 24) | (((uint32_t)(c7)) << 28))
#define WS_DISPLAY_SHADE_LUT_DEFAULT WS_DISPLAY_SHADE_LUT(0, 2, 4, 6, 9, 11, 13, 15)

/**
 * @brief Create an RGB color.
 *
 * @param r The red component (0-15).
 * @param g The red component (0-15).
 * @param b The red component (0-15).
 */
#define WS_RGB(r, g, b) (((r) << 8) | ((g) << 4) | (b))

 /**
  * @brief Configure the shade LUT.
  *
  * To learn more about the shade LUT, see @ref video_pipeline.
  *
  * @param lut The shade LUT configuration. Usage of the #GRAY_LUT macro is recommended. A default configuration is provided via #GRAY_LUT_DEFAULT .
  */
__attribute__((no_assume_ds_data, no_assume_ss_data, save_all))
void ws_display_set_shade_lut(uint32_t lut);

/**
 * @brief Place a map of tiles on the screen.
 *
 * @param dest Pointer to the destination screen.
 * @param src Pointer to the source map.
 * @param x Destination X position, in tiles.
 * @param y Destination Y position, in tiles.
 * @param width Destination width, in tiles (1-32).
 * @param height Destination height, in tiles (1-32).
 */
static inline void ws_screen_put_tiles(void ws_iram *dest, const void __far *src, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
	void __libws_screen_put_tiles(void ws_iram *dest, const void __far *src, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t pitch);
	__libws_screen_put_tiles(dest, src, x, y, width, height, width);
}

/**
 * @brief Place a map of tiles on the screen.
 * This varianta llows specifying the source X position, Y position and width.
 *
 * @param dest Pointer to the destination screen.
 * @param src Pointer to the source map.
 * @param sx Source X position, in tiles.
 * @param sy Source Y position, in tiles.
 * @param pitch Source width, in tiles.
 * @param dx Destination X position, in tiles.
 * @param dy Destination Y position, in tiles.
 * @param width Destination width, in tiles (1-32).
 * @param height Destination height, in tiles (1-32).
 */
static inline void ws_screen_put_tiles_ex(void ws_iram *dest, const void __far *src, uint16_t sx, uint16_t sy, uint16_t pitch, uint16_t dx, uint16_t dy, uint16_t width, uint16_t height) {
	void __libws_screen_put_tiles(void ws_iram *dest, const void __far *src, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t pitch);
	__libws_screen_put_tiles(dest, ((const uint16_t __far*) src) + (sy * pitch) + sx, dx, dy, width, height, pitch);
}

/**
 * @brief Copy a map of tiles from the screen.
 *
 * @param dest Pointer to the destination area.
 * @param src Pointer to the source screen.
 * @param x Source X position, in tiles.
 * @param y Source Y position, in tiles.
 * @param width Width, in tiles.
 * @param height Height, in tiles.
 */
void ws_screen_get_tiles(void __far *dest, const void ws_iram *src, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

/**
 * @brief Fill an area on the screen with a given tile.
 *
 * @param dest Pointer to the destination screen.
 * @param src The tile to fill the area with.
 * @param x Destination X position, in tiles.
 * @param y Destination Y position, in tiles.
 * @param width Width, in tiles.
 * @param height Height, in tiles.
 */
void ws_screen_fill_tiles(void ws_iram *dest, uint16_t src, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

/**
 * @brief Modify an area on the screen with given data.
 *
 * @param dest Pointer to the destination screen.
 * @param mask The mask to AND the area with.
 * @param value The value to OR the area with.
 * @param x Destination X position, in tiles.
 * @param y Destination Y position, in tiles.
 * @param width Width, in tiles.
 * @param height Height, in tiles.
 */
void ws_screen_modify_tiles(void ws_iram *dest, uint16_t mask, uint16_t value, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

/**
 * @brief Put a tile on the screen.
 *
 * @param dest Pointer to the destination screen.
 * @param src The tile to put.
 * @param x Destination X position, in tiles.
 * @param y Destination Y position, in tiles.
 */
static inline void ws_screen_put_tile(void ws_iram *dest, uint16_t src, uint16_t x, uint16_t y) {
	((uint16_t ws_iram*) dest)[((y & 0x1F) << 5) | (x & 0x1F)] = src;
}

/**
 * @brief Get a tile on the screen.
 *
 * @param src Pointer to the source screen.
 * @param x Destination X position, in tiles.
 * @param y Destination Y position, in tiles.
 */
static inline uint16_t ws_screen_get_tile(void ws_iram *src, uint16_t x, uint16_t y) {
	return ((uint16_t ws_iram*) src)[((y & 0x1F) << 5) | (x & 0x1F)];
}

/**@}*/

#endif /* LIBWS_DISPLAY_H_ */
