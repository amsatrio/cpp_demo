#include "animal.h"

// Implementation of Animal methods
int Animal::get_foot_count() const {
    return 4; 
}

void Animal::set_name(string name) {
    name_ = std::move(name);
}

string Animal::get_name() const {
    return name_;
}

// Implementation of Dog
string_view Dog::make_sound() const {
    return "Woof!";
}

// Implementation of Cat
string_view Cat::make_sound() const {
    return "Meow!";
}

// Implementation of Mouse
string_view Mouse::make_sound() const {
    return "Squeak!";
}