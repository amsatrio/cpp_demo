#include <iostream>
#include <string>
#include "animal.cpp"

using namespace std;

class Dog: public Animal {
    public:
        Dog(string n) : Animal(n) {}
        void makeSound() const override {
            cout << getName() << " woof" << endl;
        }
};