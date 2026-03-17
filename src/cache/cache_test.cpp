#include "../../src/util/generator.h"
#include "cache.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

std::vector<uint8_t> string_to_binary(std::string value) {
    return std::vector<uint8_t>(value.begin(), value.end());
}
std::string binary_to_string(std::vector<uint8_t> data) {
    std::string result(data.begin(), data.end());
    return result;
}

int main() {
    std::string key1 = "user_123";
    std::vector<uint8_t> val1 = string_to_binary("John Doe");
    std::string key2 = "session_token";
    std::vector<uint8_t> val2 = string_to_binary("ABC-987");
    std::vector<uint8_t> newVal1 = string_to_binary("Jane Doe");
    std::string missingKey = "ghost";

    std::cout << "--- Running Cache In Memory Tests ---" << std::endl;
    std::unique_ptr<Cache> cache = std::make_unique<CacheInMemory>();

    cache->set(key1, val1);
    assert(cache->get(key1) == string_to_binary("John Doe"));
    std::cout << "[PASS] Set and Get: " << key1 << std::endl;

    assert(cache->exists(key1) == true);
    assert(cache->exists("non_existent") == false);
    std::cout << "[PASS] Exists check" << std::endl;

    cache->set(key1, newVal1);
    assert(cache->get(key1) == string_to_binary("Jane Doe"));
    std::cout << "[PASS] Overwrite existing key" << std::endl;

    assert(cache->get(missingKey) == std::vector<uint8_t>{});
    std::cout << "[PASS] Missing key returns empty string" << std::endl;

    std::cout << "--- Running Cache In Storage Tests ---" << std::endl;
    cache = std::make_unique<CacheInStorage>();

    cache->set(key1, val1);
    // std::cout << result << std::endl;
    assert(cache->get(key1) == string_to_binary("John Doe"));
    std::cout << "[PASS] Set and Get: " << key1 << std::endl;

    assert(cache->exists(key1) == true);
    assert(cache->exists("non_existent") == false);
    std::cout << "[PASS] Exists check" << std::endl;

    cache->set(key1, newVal1);
    assert(cache->get(key1) == string_to_binary("Jane Doe"));
    std::cout << "[PASS] Overwrite existing key" << std::endl;

    assert(cache->get(missingKey) == std::vector<uint8_t>{});
    std::cout << "[PASS] Missing key returns empty string" << std::endl;

    // std::string key = "";
    // for (size_t i = 0; i < 1000; i++) {
    //     key = generate_random_string(10);
    //     std::string value = generate_random_string(20);

    //     cache->set(key, value);
    // }
    // assert(cache->exists(key) == true);
}