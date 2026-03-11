#include <string>
#include "generator.h"
#include <assert.h>
#include <iostream>

int main() {
    std::cout << "--- Running Generator Tests ---" << std::endl;
    
    std::string a = generate_random_string(10);
    assert(a.length() == 10);

    std::cout << "[PASS] Get random string" << std::endl;
}