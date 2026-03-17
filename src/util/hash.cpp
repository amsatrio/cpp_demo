#include "hash.h"

std::string hardware_hash(const std::string& s) {
    uint32_t hash = 0;
    for (char c : s) {
        hash = _mm_crc32_u8(hash, c);
    }
    return std::to_string(hash);
}