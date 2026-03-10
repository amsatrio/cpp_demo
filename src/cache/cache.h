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
    public:
        virtual ~CacheInStorage() = default;
        
        void set(std::string& key, std::string& value) override;
        std::string get(std::string& key) override;
        bool exists(const std::string& key) override;
};