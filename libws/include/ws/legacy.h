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

#if defined(LIBWS_VERSION) && LIBWS_VERSION < 202505L

#define ws_dma_set_sourcei ws_gdma_set_sourcei
#define ws_dma_set_sourcep ws_gdma_set_sourcep
#define ws_dma_set_source ws_gdma_set_source
#define ws_dma_copy_words ws_gdma_copyp
#define ws_dma_copy_words_linear ws_gdma_copyi
#define ws_dma_opt_copy_words ws_gdma_maybe_copy

#endif

#endif /* LIBWS_LEGACY_H_ */
