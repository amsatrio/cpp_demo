#include "cache.pb.h"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class Cache {
  public:
    virtual ~Cache() = default;

    virtual void set(std::string &key, std::vector<uint8_t> &value) {};
    virtual std::vector<uint8_t> get(std::string &key) {
        return std::vector<uint8_t>{};
    };
    virtual bool exists(const std::string &key) { return false; };
};

class CacheInMemory : public Cache {
  private:
    std::unordered_map<std::string, CacheObject> database;

  public:
    virtual ~CacheInMemory() = default;

    void set(std::string &key, std::vector<uint8_t> &value) override;
    std::vector<uint8_t> get(std::string &key) override;
    bool exists(const std::string &key) override;
};

class CacheInStorage : public Cache {
  private:
    const std::string cache_directory = "./data";

  public:
    CacheInStorage();
    virtual ~CacheInStorage() = default;

    void set(std::string &key, std::vector<uint8_t> &value) override;
    std::vector<uint8_t> get(std::string &key) override;
    bool exists(const std::string &key) override;
};