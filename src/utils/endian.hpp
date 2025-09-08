// Derived from DevilutionX's Source/utils/endian.hpp
// License: https://github.com/diasurgical/devilutionX/blob/master/LICENSE.md

#pragma once

#include <cstdint>

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
inline uint16_t SwapLE16(uint16_t x) { return __builtin_bswap16(x); }
inline uint32_t SwapLE32(uint32_t x) { return __builtin_bswap32(x); }
#else
inline uint16_t SwapLE16(uint16_t x) { return x; }
inline uint32_t SwapLE32(uint32_t x) { return x; }
#endif
