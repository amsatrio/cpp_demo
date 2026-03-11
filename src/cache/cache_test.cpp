#include <iostream>
#include <cassert>
#include <memory>
#include "cache.h"
#include "../../src/util/generator.h"

int main() {
    std::string key1 = "user_123";
    std::string val1 = "John Doe";
    std::string key2 = "session_token";
    std::string val2 = "ABC-987";
    std::string newVal1 = "Jane Doe";
    std::string missingKey = "ghost";

    std::cout << "--- Running Cache In Memory Tests ---" << std::endl;
    std::unique_ptr<Cache> cache = std::make_unique<CacheInMemory>();

    cache->set(key1, val1);
    assert(cache->get(key1) == "John Doe");
    std::cout << "[PASS] Set and Get: " << key1 << std::endl;

    assert(cache->exists(key1) == true);
    assert(cache->exists("non_existent") == false);
    std::cout << "[PASS] Exists check" << std::endl;

    cache->set(key1, newVal1);
    assert(cache->get(key1) == "Jane Doe");
    std::cout << "[PASS] Overwrite existing key" << std::endl;

    assert(cache->get(missingKey) == "");
    std::cout << "[PASS] Missing key returns empty string" << std::endl;

    std::cout << "--- Running Cache In Storage Tests ---" << std::endl;
    cache = std::make_unique<CacheInStorage>();

    cache->set(key1, val1);
    std::cout << cache->get(key1) << std::endl;
    assert(cache->get(key1) == "John Doe");
    std::cout << "[PASS] Set and Get: " << key1 << std::endl;

    assert(cache->exists(key1) == true);
    assert(cache->exists("non_existent") == false);
    std::cout << "[PASS] Exists check" << std::endl;

    cache->set(key1, newVal1);
    assert(cache->get(key1) == "Jane Doe");
    std::cout << "[PASS] Overwrite existing key" << std::endl;

    assert(cache->get(missingKey) == "");
    std::cout << "[PASS] Missing key returns empty string" << std::endl;

    std::string key = "";
    for (size_t i = 0; i < 1000; i++) {
        key = generate_random_string(10);
        std::string value = generate_random_string(20);

        cache->set(key, value);
    }
    assert(cache->exists(key) == true);
    
}