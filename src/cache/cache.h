#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <set>
#include <vector>

class Cache {
    public:
        virtual ~Cache() = default;

        virtual void set(std::string& key, std::string& value) {};
        virtual std::string get(std::string& key) { return std::string(); };
        virtual bool exists(const std::string& key) { return false; };
};

enum class CacheType {String, List, Set, Hash};

struct CacheObject {
    CacheType type;
    std::variant<std::string, std::vector<std::string>, std::set<std::string>> data;
    long long expired_at = -1;
};

class CacheInMemory: public Cache {
    private:
        std::unordered_map<std::string, CacheObject> database;
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