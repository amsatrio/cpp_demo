#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>

class Cache {
    public:
        virtual ~Cache() = default;

        virtual void set(std::string& key, std::string& value) {};
        virtual std::string get(std::string& key) { return std::string(); };
        virtual bool exists(const std::string& key) { return false; };
};
class CacheInMemory: public Cache {
    private:
        std::unordered_map<std::string, std::string> map;
    public:
        virtual ~CacheInMemory() = default;
        
        void set(std::string& key, std::string& value) override;
        std::string get(std::string& key) override;
        bool exists(const std::string& key) override;
};
class CacheInStorage: public Cache {
    private:
        const std::string cache_directory = "./data";
        // in byte
        const std::uintmax_t cache_file_size_threshold = 1000;
    public:
        CacheInStorage();
        virtual ~CacheInStorage() = default;
        
        void set(std::string& key, std::string& value) override;
        std::string get(std::string& key) override;
        bool exists(const std::string& key) override;
};