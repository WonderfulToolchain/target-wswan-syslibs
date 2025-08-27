/**
 * Copyright (c) 2025 Adrian "asie" Siekierka
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

#include <stdbool.h>
#include <stdint.h>
#include <wonderful.h>
#include "ws/ports.h"
#include "ws/cart/rtc.h"

bool ws_cart_rtc_wait_ready(void) {
	uint16_t timeout = 0;

	while (--timeout) {
		uint8_t status = inportb(WS_CART_RTC_CTRL_PORT);

		// Not ready, not busy => Done
		if (!(status & (WS_CART_RTC_CTRL_READY | WS_CART_RTC_CTRL_ACTIVE))) return true;
		if (status & WS_CART_RTC_CTRL_READY) return true;
	}

	return false;
}

uint16_t ws_cart_rtc_read(uint8_t command, void __wf_cram* buffer, uint16_t length) {
	uint8_t __wf_cram* buffer8 = (uint8_t __wf_cram*) buffer;
	uint16_t bytes = 0;
	uint16_t timeout = 0;

	if (!ws_cart_rtc_wait_ready()) return false;

	outportb(WS_CART_RTC_CTRL_PORT, command | WS_CART_RTC_CTRL_ACTIVE);
	while (--timeout) {
		uint8_t status = inportb(WS_CART_RTC_CTRL_PORT);

		// Not ready, not busy => Done
		if (!(status & (WS_CART_RTC_CTRL_READY | WS_CART_RTC_CTRL_ACTIVE))) break;

		// Ready => Read byte
		if (status & WS_CART_RTC_CTRL_READY) {
			if (bytes < length)
				buffer8[bytes] = inportb(WS_CART_RTC_DATA_PORT);
			else
				inportb(WS_CART_RTC_DATA_PORT);
			bytes++;
		}
		// Inactive => Finished reading
		if (!(status & WS_CART_RTC_CTRL_ACTIVE)) break;
	}

	return bytes;
}

uint16_t ws_cart_rtc_write(uint8_t command, const void __wf_cram* buffer, uint16_t length) {
	uint8_t __wf_cram* buffer8 = (uint8_t __wf_cram*) buffer;
	uint16_t bytes = 0;
	uint16_t timeout = 0;

	if (!ws_cart_rtc_wait_ready()) return false;

	if (length)
		outportb(WS_CART_RTC_DATA_PORT, buffer8[bytes++]);
	outportb(WS_CART_RTC_CTRL_PORT, command | WS_CART_RTC_CTRL_ACTIVE);
	while (--timeout) {
		uint8_t status = inportb(WS_CART_RTC_CTRL_PORT);

		// Inactive => Finished writing
		if (!(status & WS_CART_RTC_CTRL_ACTIVE)) break;

		// Ready => Write byte
		if (status & WS_CART_RTC_CTRL_READY) {
			if (bytes < length)
				outportb(WS_CART_RTC_DATA_PORT, bytes < length ? buffer8[bytes] : 0x00);
			bytes++;
		}
	}

	return bytes;
}
