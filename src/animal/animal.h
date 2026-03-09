#pragma once
#include <string>
#include <string_view>

using namespace std;

class Animal {
public:
    virtual ~Animal() = default;

    virtual string_view make_sound() const = 0;
    
    virtual int get_foot_count() const { return 4; }

    void set_name(string name) { name_ = std::move(name); }
    string get_name() const { return name_; }

protected:
    string name_;
};

class Dog : public Animal {
public:
    string_view make_sound() const override { return "Woof!"; }
};

class Cat : public Animal {
public:
    string_view make_sound() const override { return "Meow!"; }
};

class Mouse : public Animal {
public:
    string_view make_sound() const override { return "Squeak!"; }
};