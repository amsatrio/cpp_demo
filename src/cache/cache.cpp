#include "cache.h"
#include "../util/hash.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>
#include <system_error>
#include <vector>

inline long long current_time_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

void CacheInMemory::set(std::string &key, std::vector<uint8_t> &value, uint64_t expired_in) {
    auto hash = hardware_hash(key);
    CacheObject obj;
    obj.set_value(value.data(), value.size());
    obj.set_expired_at(current_time_ms() + expired_in);
    database[hash] = std::move(obj);
}

std::vector<uint8_t> CacheInMemory::get(std::string &key) {
    auto it = CacheInMemory::database.find(hardware_hash(key));

    std::vector<uint8_t> result = {};

    if (it == database.end())
        return result;

    if (it->second.get_expired_at() != -1 &&
        it->second.get_expired_at() < current_time_ms()) {
        database.erase(it);
        return result;
    }

    return it->second.get_value();
}

bool CacheInMemory::exists(const std::string &key) {
    return CacheInMemory::database.count(hardware_hash(key)) > 0;
}

CacheInStorage::CacheInStorage() {
    // create directory if not exists
    std::error_code ec;
    if (!std::filesystem::is_directory(cache_directory)) {
        std::filesystem::create_directories(cache_directory, ec);
    }
}
void CacheInStorage::set(std::string &key, std::vector<uint8_t> &value, uint64_t expired_in) {
    CacheObject obj;
    obj.set_value(value.data(), value.size());
    obj.set_expired_at(current_time_ms() + expired_in);

    std::fstream output(cache_directory + "/" + hardware_hash(key),
                        std::ios::out | std::ios::binary | std::ios::trunc);

    if (!obj.SerializeToOstream(&output)) {
        std::cout << "write object error: " << std::endl;
    }
    output.close();
}

std::vector<uint8_t> CacheInStorage::get(std::string &key) {
    std::string cache_file_path = cache_directory + "/" + hardware_hash(key);
    if (!std::filesystem::exists(cache_file_path)) {
        return {};
    }

    std::ifstream input(cache_file_path, std::ios::in | std::ios::binary);
    if (!input) {
        return {};
    }

    CacheObject object;
    if (!object.ParseFromIstream(&input)) {
        return {};
    }

    input.close();
    if (object.get_expired_at() != -1 && object.get_expired_at() < current_time_ms()) {
        std::filesystem::remove(cache_file_path);
        return {};
    }

    return object.get_value();
}

bool CacheInStorage::exists(const std::string &key) {
    std::string cache_file_path = cache_directory + "/" + hardware_hash(key);
    return std::filesystem::exists(cache_file_path);
}
