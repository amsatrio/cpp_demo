#include <iostream>
#include <string>
#include "animal.cpp"

using namespace std;

class Cat: public Animal {
    public:
        Cat(string n) : Animal(n) {}
        void makeSound() const override {
            cout << getName() << " meow" << endl;
        }
};