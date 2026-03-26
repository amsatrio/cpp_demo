#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>

class CacheObject {
  private:
    std::vector<uint8_t> value;
    uint64_t expired_at;
  public:
    void set_expired_at(uint64_t data) {
      expired_at = data;
    }
    void set_value(const uint8_t *data, uint8_t size) {
      value.assign(data, data + size);
      value.shrink_to_fit();
    }
    const std::vector<uint8_t>& get_value() {
      return value;
    }
    uint64_t get_expired_at() {
      return expired_at;
    }
    bool SerializeToOstream(std::ostream* output) const {
      if (!output || !*output) return false;
      output->write(reinterpret_cast<const char*>(&expired_at), sizeof(expired_at));
      size_t v_size = value.size();
      output->write(reinterpret_cast<const char*>(&v_size), sizeof(v_size));
      if (v_size > 0) {
          output->write(reinterpret_cast<const char*>(value.data()), v_size);
      }

      return output->good();
  }

  bool ParseFromIstream(std::istream* input) {
      if (!input || !*input) return false;

      input->read(reinterpret_cast<char*>(&expired_at), sizeof(expired_at));

      size_t v_size = 0;
      input->read(reinterpret_cast<char*>(&v_size), sizeof(v_size));

      if (input->good()) {
          value.resize(v_size);
          if (v_size > 0) {
              input->read(reinterpret_cast<char*>(value.data()), v_size);
          }
      }

      return !input->fail();
  }
};

class Cache {
  public:
    virtual ~Cache() = default;

    virtual void set(std::string &key, std::vector<uint8_t> &value, uint64_t expired_in) {};
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

    void set(std::string &key, std::vector<uint8_t> &value, uint64_t expired_in) override;
    std::vector<uint8_t> get(std::string &key) override;
    bool exists(const std::string &key) override;
};

class CacheInStorage : public Cache {
  private:
    const std::string cache_directory = "./data";

  public:
    CacheInStorage();
    virtual ~CacheInStorage() = default;

    void set(std::string &key, std::vector<uint8_t> &value, uint64_t expired_in) override;
    std::vector<uint8_t> get(std::string &key) override;
    bool exists(const std::string &key) override;
};