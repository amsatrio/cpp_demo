#include "cache.h"
#include <cstdint>
#include <drogon/HttpAppFramework.h>
#include <iostream>
#include <string>
#include <trantor/net/TcpServer.h>

const char *findCRLF(const char *start, const char *end) {
    for (const char *p = start; p < end - 1; ++p) {
        if (*p == '\r' && *(p + 1) == '\n') {
            return p;
        }
    }
    return nullptr;
}

int main() {
    auto loop = drogon::app().getLoop();

    trantor::InetAddress addr("0.0.0.0", 6379);

    auto server =
        std::make_shared<trantor::TcpServer>(loop, addr, "RedisClone");

    std::unique_ptr<Cache> cache = std::make_unique<CacheInMemory>();

    server->setRecvMessageCallback(
        [&cache](const trantor::TcpConnectionPtr &conn,
                 trantor::MsgBuffer *buf) {
            std::string payload(buf->peek(), buf->readableBytes());
            std::cout << "Received: " << payload << std::endl;

            if (payload.find("HELLO") != std::string::npos) {
                conn->send("%1\r\n$6\r\nserver\r\n$10\r\nRedisClone\r\n");
            }
            if (payload.find("CLIENT") != std::string::npos) {
                size_t pos = payload.find("CLIENT");
                while (pos != std::string::npos) {
                    conn->send("+OK\r\n");
                    pos = payload.find("CLIENT", pos + 1);
                }
            } else if (payload.find("GET") != std::string::npos) {

                const char *start = buf->peek();
                const char *end = start + buf->readableBytes();

                const char *crlf = findCRLF(start, end);
                if (!crlf)
                    return;

                int numElements = std::stoi(std::string(start + 1, crlf));
                const char *current = crlf + 2;

                std::string command, key;
                std::vector<uint8_t> value;

                for (int i = 0; i < numElements; ++i) {
                    if (current >= end || *current != '$')
                        break;

                    const char *nextCrlf = findCRLF(current, end);
                    int len = std::stoi(std::string(current + 1, nextCrlf));
                    current = nextCrlf + 2;

                    if (i == 0)
                        command = std::string(current, len);
                    else if (i == 1)
                        key = std::string(current, len);

                    current += len + 2;
                }
                value = cache->get(key);
                std::cout << "Command: " << command << " | Key: " << key
                          << std::endl;
                std::cout << "Value Size: " << value.size() << " bytes"
                          << std::endl;

                if (value.size() > 0) {
                    std::string response =
                        "$" + std::to_string(value.size()) + "\r\n";
                    conn->send(response);
                    std::string value_string(value.begin(), value.end());
                    conn->send(value_string);
                    conn->send("\r\n");
                    return;
                }
                conn->send("_\r\n");
            } else if (payload.find("SET") != std::string::npos) {

                const char *start = buf->peek();
                const char *end = start + buf->readableBytes();

                const char *crlf = findCRLF(start, end);
                if (!crlf)
                    return;

                int numElements = std::stoi(std::string(start + 1, crlf));
                const char *current = crlf + 2;

                std::string command, key;
                std::vector<uint8_t> value;

                for (int i = 0; i < numElements; ++i) {
                    if (current >= end || *current != '$')
                        break;

                    const char *nextCrlf = findCRLF(current, end);
                    int len = std::stoi(std::string(current + 1, nextCrlf));
                    current = nextCrlf + 2;

                    if (i == 0)
                        command = std::string(current, len);
                    else if (i == 1)
                        key = std::string(current, len);
                    else if (i == 2) {
                        value.assign(current, current + len);
                    }

                    current += len + 2;
                }

                std::cout << "Command: " << command << " | Key: " << key
                          << std::endl;
                std::cout << "Value Size: " << value.size() << " bytes"
                          << std::endl;

                cache->set(key, value);

                conn->send("+OK\r\n");
            }

            buf->retrieveAll();
        });

    server->start();

    drogon::app().run();

    return 0;
}
