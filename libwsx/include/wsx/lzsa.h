#pragma once
#include <stdint.h>

uint16_t wsx_lzsa1_decompress(void __far* dest, const void __far* src);
uint16_t wsx_lzsa2_decompress(void __far* dest, const void __far* src);
