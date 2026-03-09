#include "hello_world.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    auto greeting = get_greeting();
    assert(greeting == "Hello World!");
    cout << "Test Passed: " << greeting << endl;
    return 0;
}