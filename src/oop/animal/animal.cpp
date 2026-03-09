#include <iostream>
#include <string>

using namespace std;

class Animal {
    private:
        string name;
    public:
        Animal(string n) : name(n) {}

        virtual void makeSound() const {
            cout << name << " make generic sound. " << endl;
        }

        string getName() const { return name; }
};