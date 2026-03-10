#include <vector>
#include <ios>
#include <fstream>
#include "cache.h"
#include <nlohmann/json.hpp>

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

void CacheInStorage::set(std::string &key, std::string &value) {
    std::fstream input("cache.json", std::ios::in);

    nlohmann::json data;

    if (input.is_open()){
        input >> data;
        input.close();
    } else {
        data = {};
    }

    data[key] = value;

    std::fstream output("cache.json", std::ios::out | std::ios::trunc);
    output << data.dump();
    output.close();
}

std::string CacheInStorage::get(std::string &key) {
    std::fstream input("cache.json", std::ios::in);

    nlohmann::json data;

    if (input.is_open()){
        input >> data;
        input.close();
    } else {
        return std::string();
    }

    if (data.contains(key)) {
        return data[key].get<std::string>();
    }

    return std::string();
}

bool CacheInStorage::exists(const std::string &key) {
    std::fstream input("cache.json", std::ios::in);

    nlohmann::json data;

    if (input.is_open()){
        input >> data;
        input.close();
    } else {
        return false;
    }

    return data.contains(key);
}
