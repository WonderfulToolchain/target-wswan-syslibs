#pragma once
#include <stdint.h>

#define WSX_PLANAR_UNPACK_MODE_1BPP_2BPP_ZERO(offset) (offset)
#define WSX_PLANAR_UNPACK_MODE_1BPP_4BPP_ZERO(offset) ((offset) | (1 << 8))

void wsx_planar_unpack(void __far* dest, uint16_t src_length, const void __far* src, uint16_t mode);
