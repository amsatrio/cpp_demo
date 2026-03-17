#include "cache.h"
#include "cache.pb.h"
#include "../util/hash.h"
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>
#include <filesystem>
#include <system_error>

inline long long current_time_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

void CacheInMemory::set(std::string &key, std::string &value){
    CacheObject obj;
    obj.set_type(CacheType::STRING);
    obj.set_data(value);
    obj.set_expired_at(-1);
    database[hardware_hash(key)] = std::move(obj);
}

std::string CacheInMemory::get(std::string &key){
    auto it = CacheInMemory::database.find(hardware_hash(key));

    if (it == database.end()) return "";

    if (it->second.expired_at() != -1 && it->second.expired_at() < current_time_ms()) {
        database.erase(it);
        return "";
    }

    return it->second.data();
}

bool CacheInMemory::exists(const std::string &key){
    return CacheInMemory::database.count(hardware_hash(key)) > 0;
}


CacheInStorage::CacheInStorage(){
    // create directory if not exists
    std::error_code ec;
    if(!std::filesystem::is_directory(cache_directory)) {
        std::filesystem::create_directories(cache_directory, ec);
    }
}
void CacheInStorage::set(std::string &key, std::string &value) {
    CacheObject obj;
    obj.set_type(CacheType::STRING);
    obj.set_data(value);
    obj.set_expired_at(-1);

    std::fstream output(cache_directory + "/" + hardware_hash(key), std::ios::out | std::ios::binary | std::ios::trunc);

    if (!obj.SerializeToOstream(&output)) {
        std::cout << "write object error: " << std::endl;
    }
}

std::string CacheInStorage::get(std::string &key) {
    std::string cache_file_path = cache_directory + "/" + hardware_hash(key);
    if (!std::filesystem::exists(cache_file_path)) {
        return "";
    }

    std::ifstream input(cache_file_path, std::ios::in | std::ios::binary);
    if(!input) {
        return "";
    }

    CacheObject object;
    if(!object.ParseFromIstream(&input)) {
        return "";
    }

    input.close();
    if(object.expired_at() != -1 && object.expired_at() < current_time_ms()) {
        std::filesystem::remove(cache_file_path);
        return "";
    }
    return object.data();
}

bool CacheInStorage::exists(const std::string &key) {
    std::string cache_file_path = cache_directory + "/" + hardware_hash(key);
    return std::filesystem::is_regular_file(cache_file_path);
}
