#include <ios>
#include <fstream>
#include "cache.h"
#include <nlohmann/json.hpp>
#include <string>

void CacheInMemory::set(std::string &key, std::string &value){
    CacheInMemory::map[key] = value;
}

std::string CacheInMemory::get(std::string &key){
    auto it = CacheInMemory::map.find(key);

    if (it != CacheInMemory::map.end()) {
        return it->second;
    }
    return "";
}

bool CacheInMemory::exists(const std::string &key){
    if (CacheInMemory::map.count(key) > 0) {
        return true;
    }
    return false;
}


CacheInStorage::CacheInStorage(){
    // create directory if not exists
    std::error_code ec;
    if(!std::filesystem::is_directory(cache_directory)) {
        std::filesystem::create_directories(cache_directory, ec);
    }
}
void CacheInStorage::set(std::string &key, std::string &value) {
    int i = 0;
    nlohmann::json data;
    bool is_exists = false;
    std::string cache_file_path;

    while (true) {
        cache_file_path = cache_directory + "/" + std::to_string(i);
        if(!std::filesystem::is_regular_file(cache_file_path)) {
            break;
        }

        std::fstream input(cache_file_path, std::ios::in);

        if (input.is_open()){
            input >> data;
            input.close();
        } else {
            break;
        }

        if (data.contains(key)) {
            is_exists = true;
            break;
        }
        i++;
    }

    if (!is_exists) {
        i = 0;
        while (true) {
            cache_file_path = cache_directory + "/" + std::to_string(i);
            if(!std::filesystem::is_regular_file(cache_file_path)) {
                break;
            }
            std::uintmax_t cache_file_size = std::filesystem::file_size(cache_file_path);
            if (cache_file_size <= cache_file_size_threshold) {
                break;
            }
            i++;
        }
    }

    std::fstream input(cache_file_path, std::ios::in);

    data = {};

    if (input.is_open()){
        input >> data;
        input.close();
    } else {
        data = {};
    }

    data[key] = value;

    std::fstream output(cache_file_path, std::ios::out | std::ios::trunc);
    output << data.dump();
    output.close();
}

std::string CacheInStorage::get(std::string &key) {

    int i = 0;
    nlohmann::json data;
    std::string value = "";
    std::string cache_file_path;

    while (true) {
        cache_file_path = cache_directory + "/" + std::to_string(i);
        if(!std::filesystem::is_regular_file(cache_file_path)) {
            break;
        }

        std::fstream input(cache_file_path, std::ios::in);

        if (input.is_open()){
            input >> data;
            input.close();
        } else {
            break;
        }

        if (data.contains(key)) {
            value = data[key].get<std::string>();
            break;
        }
        i++;
    }

    return value;
}

bool CacheInStorage::exists(const std::string &key) {
    int i = 0;
    nlohmann::json data;
    bool is_exists = false;
    std::string cache_file_path;

    while (true) {
        cache_file_path = cache_directory + "/" + std::to_string(i);
        if(!std::filesystem::is_regular_file(cache_file_path)) {
            break;
        }

        std::fstream input(cache_file_path, std::ios::in);

        if (input.is_open()){
            input >> data;
            input.close();
        } else {
            break;
        }

        if (data.contains(key)) {
            is_exists = true;
            break;
        }
        i++;
    }

    return is_exists;
}
