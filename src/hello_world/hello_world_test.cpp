#include "hello_world.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    std::cout << "--- Running Hello World Tests ---" << std::endl;

    auto greeting = get_greeting();
    assert(greeting == "Hello World!");
    cout << "[PASS] Get greeting: " << greeting << endl;
    return 0;
}