#include "animal.h"
#include <cassert>
#include <iostream>
#include <memory>

using namespace std;

int main() {
  unique_ptr<Animal> dog = make_unique<Dog>();
  unique_ptr<Animal> cat = make_unique<Cat>();
  unique_ptr<Animal> mouse = make_unique<Mouse>();

  assert(dog->make_sound() == "Woof!");
  assert(cat->make_sound() == "Meow!");
  assert(mouse->make_sound() == "Squeak!");

  dog->set_name("d");
  cat->set_name("c");
  mouse->set_name("m");

  assert(dog->get_name() == "d");
  assert(cat->get_name() == "c");
  assert(mouse->get_name() == "m");

  cout << "All Animal tests passed (C++23)!" << endl;
  return 0;
}