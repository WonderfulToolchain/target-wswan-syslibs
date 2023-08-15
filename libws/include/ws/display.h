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

#ifndef __WF_LIBWS_DISPLAY_H__
#define __WF_LIBWS_DISPLAY_H__

#include <stdbool.h>
#include <stdint.h>
#include <wonderful.h>

/** \file display.h
 * Functionality related to the display.
 */

#define DISPLAY_WIDTH 28
#define DISPLAY_HEIGHT 18
#define DISPLAY_WIDTH_PX (DISPLAY_WIDTH * TILE_WIDTH)
#define DISPLAY_HEIGHT_PX (DISPLAY_HEIGHT * TILE_HEIGHT)

#define TILE_WIDTH 8
#define TILE_HEIGHT 8
#define TILE_LENGTH 16
#define TILE_4BPP_LENGTH 32

typedef struct {
	uint8_t row[TILE_HEIGHT][2];
} ws_tile_t;

typedef struct {
	uint8_t row[TILE_HEIGHT][4];
} ws_tile_4bpp_t;

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

typedef struct {
	union {
		struct {
			uint16_t tile : 9;
			uint8_t palette : 4;
			uint8_t bank : 1;
			bool flip_h : 1;
			bool flip_v : 1;
		};
		uint16_t attr;
	};
} ws_screen_cell_t;

#define SCR_WIDTH 32
#define SCR_HEIGHT 32
#define SCR_WIDTH_PX (SCR_WIDTH * TILE_WIDTH)
#define SCR_HEIGHT_PX (SCR_HEIGHT * TILE_HEIGHT)

typedef struct {
	union {
		struct {
			uint16_t tile : 9;
			uint8_t palette : 3;
			bool inside : 1;
			bool priority : 1;
			bool flip_h : 1;
			bool flip_v : 1;
		};
		uint16_t attr;
	};
	uint8_t y;
	uint8_t x;
} ws_sprite_t;

#define SPR_ATTR_PALETTE(x) ((x) << 9)
#define SPR_ATTR_PALETTE_MASK	(0x7 << 9)
#define SPR_ATTR_INSIDE   0x1000
#define SPR_ATTR_PRIORITY 0x2000
#define SPR_ATTR_FLIP_H   0x4000
#define SPR_ATTR_FLIP_V   0x8000

#define SPR_MAX_COUNT 128

// legacy defines

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

#define ws_scr_entry_t ws_screen_tile_t

#define SPR_ENTRY_PALETTE(x) ((x) << 9)
#define SPR_ENTRY_PALETTE_MASK	(0x7 << 9)
#define SPR_ENTRY_INSIDE   0x1000
#define SPR_ENTRY_PRIORITY 0x2000
#define SPR_ENTRY_FLIP_H   0x4000
#define SPR_ENTRY_FLIP_V   0x8000

/**
 * @addtogroup DefinesVideoMem Defines - Video memory
 * @{
 */

/**
 * @brief Pointer to tile.
 *
 * @param i Tile index (0-511).
 */
#define MEM_TILE(i) ((uint8_t __wf_iram*) (0x2000 + ((i) << 4)))

/**
 * @brief Pointer to 4bpp tile.
 *
 * @param i Tile index (0-1023).
 */
#define MEM_TILE_4BPP(i) MEM_TILE_4BPP_BANK0(i)

/**
 * @brief Pointer to 4bpp tile in bank 0 (0-511).
 *
 * @param i Tile index (0-511).
 */
#define MEM_TILE_4BPP_BANK0(i) ((uint8_t __wf_iram*) (0x4000 + ((i) << 5)))

/**
 * @brief Pointer to 4bpp tile in bank 1 (512-1023).
 *
 * @param i Tile index (0-511).
 */
#define MEM_TILE_4BPP_BANK1(i) ((uint8_t __wf_iram*) (0x8000 + ((i) << 5)))

/**
 * @brief Pointer to color palette.
 *
 * @param i Color palette (0-15).
 */
#define MEM_COLOR_PALETTE(i) ((uint16_t __wf_iram*) (0xFE00 + ((i) << 5)))

/**
 * @brief Pointer to screen color palette.
 *
 * @param i Color palette (0-15).
 */
#define MEM_SCR_PALETTE MEM_COLOR_PALETTE

/**
 * @brief Pointer to sprite color palette.
 *
 * @param i Color palette (0-7).
 */
#define MEM_SPR_PALETTE(i) ((uint16_t __wf_iram*) (0xFF00 + ((i) << 5)))

/**@}*/

#define SHADE_LUT(c0, c1, c2, c3, c4, c5, c6, c7) \
	(((uint32_t)(c0)) | (((uint32_t)(c1)) << 4) | (((uint32_t)(c2)) << 8) | (((uint32_t)(c3)) << 12) | \
	(((uint32_t)(c4)) << 16) | (((uint32_t)(c5)) << 20) | (((uint32_t)(c6)) << 24) | (((uint32_t)(c7)) << 28))
#define SHADE_LUT_DEFAULT SHADE_LUT(0, 2, 4, 6, 9, 11, 13, 15)

/**
 * @addtogroup Display Functions - Display
 * @{
 */

/**
 * @brief Create an RGB color.
 *
 * @param r The red component (0-15).
 * @param g The red component (0-15).
 * @param b The red component (0-15).
 */
#define RGB(r, g, b) (((r) << 8) | ((g) << 4) | (b))

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
 * @param width Width, in tiles.
 * @param height Height, in tiles.
 */
void ws_screen_put_tiles(void __wf_iram* dest, const void __far* src, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

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
void ws_screen_get_tiles(void __far* dest, const void __wf_iram* src, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

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
void ws_screen_fill_tiles(void __wf_iram* dest, uint16_t src, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

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
void ws_screen_modify_tiles(void __wf_iram* dest, uint16_t mask, uint16_t value, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

/**
 * @brief Put a tile on the screen.
 *
 * @param dest Pointer to the destination screen.
 * @param src The tile to put.
 * @param x Destination X position, in tiles.
 * @param y Destination Y position, in tiles.
 */
static inline void ws_screen_put_tile(void __wf_iram* dest, uint16_t src, uint16_t x, uint16_t y) {
	((uint16_t __wf_iram*) dest)[((y & 0x1F) << 5) | (x & 0x1F)] = src;
}

/**
 * @brief Get a tile on the screen.
 *
 * @param src Pointer to the source screen.
 * @param x Destination X position, in tiles.
 * @param y Destination Y position, in tiles.
 */
static inline uint16_t ws_screen_get_tile(void __wf_iram* src, uint16_t x, uint16_t y) {
	return ((uint16_t __wf_iram*) src)[((y & 0x1F) << 5) | (x & 0x1F)];
}
/**@}*/

#endif /* __WF_LIBWS_DISPLAY_H__ */
