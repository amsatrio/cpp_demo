#include "animal.h"
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

int main() {
    vector<unique_ptr<Animal>> zoo;
    zoo.push_back(make_unique<Dog>());
    zoo.push_back(make_unique<Cat>());
    zoo.push_back(make_unique<Mouse>());

    assert(zoo[0]->make_sound() == "Woof!");
    assert(zoo[1]->make_sound() == "Meow!");
    assert(zoo[2]->make_sound() == "Squeak!");

    for(const auto& animal : zoo) {
        assert(animal->get_foot_count() == 4);
    }

    cout << "All Animal tests passed (C++23)!" << endl;
    return 0;
}