#include <string>
#include <random>

std::string generate_random_string(int length) {
    const std::string characters =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string random_string;
    random_string.reserve(length);

    for (int i = 0; i < length; i++) {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}