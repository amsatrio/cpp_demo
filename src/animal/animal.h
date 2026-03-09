#pragma once
#include <string>
#include <string_view>

using namespace std;

class Animal {
public:
    virtual ~Animal() = default;

    virtual string_view make_sound() const = 0;
    
    virtual int get_foot_count() const;

    void set_name(string name);
    string get_name() const;

protected:
    string name_;
};

class Dog : public Animal {
public:
    string_view make_sound() const override;
};

class Cat : public Animal {
public:
    string_view make_sound() const override;
};

class Mouse : public Animal {
public:
    string_view make_sound() const override;
};