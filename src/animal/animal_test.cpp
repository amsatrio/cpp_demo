#include "animal.h"
#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

int main() {
    unique_ptr<Animal> dog = make_unique<Dog>();
    unique_ptr<Animal> cat = make_unique<Cat>();
    unique_ptr<Animal> mouse = make_unique<Mouse>();

    assert(dog->make_sound() == "Woof!");
    assert(cat->make_sound() == "Meow!");
    assert(mouse->make_sound() == "Squeak!");

    cout << "All Animal tests passed (C++23)!" << endl;
    return 0;
}