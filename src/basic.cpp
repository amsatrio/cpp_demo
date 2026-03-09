#include <iostream>
using namespace std;

void helloWorld() {
	cout << string(5, '=') << " HELLO WORLD" << endl;

	cout << "Hello World!" << endl;
}
void ifElse() {
	cout << string(5, '=') << " IF ELSE STATEMENT" << endl;

	int status = 0;
	if (status == 1) {
		cout << "true" << endl;
	} else {
		cout << "false" << endl;
	}
}
void forLoop() {
	cout << string(5, '=') << " FOR LOOP" << endl;
	int a = 0;
	for (size_t i = 0; i < 3; i++) {
		a++;
	}
	cout << a << endl;	
}
void whileLoop() {
	cout << string(5, '=') << " WHILE LOOP" << endl;
	int a = 0;
	while (a < 4) {
		a++;
	}
	cout << a << endl;
}
void switchCase() {
	cout << string(5, '=') << " SWITCH CASE" << endl;

	int a = 0;
	switch (a) {
	case 0:
		a = 1;
		break;
	case 1:
		a = 2;
		break;
	default:
		a = -1;
		break;
	}
	cout << a << endl;
}
void arrayBasic(){
	cout << string(5, '=') << " ARRAY BASIC" << endl;

	// initialization
	int a[3] = {};
	int aLength = sizeof(a) / sizeof(*a);

	// modification
	for (size_t i = 0; i < aLength; i++) {
		a[i] = i;
	}

	// print
	for (size_t i = 0; i < aLength; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
class Book {
	public:
		string title;
		string author;
		int year;
};
class Dog {
	public :
		void bark(int a) {
			cout << "Woof!" << a << endl;
		}
};
class Car {
	private:
		string brand;
		string model;
	public:
		Car() {
			brand = "unknown";
			model = "unknown";
		}
		Car (string b, string m) {
			brand = b;
			model = m;
		}

		void print() {
			cout << brand << " " << model << endl;
		}
};
class Company{
	private:
		int salary;
	public:
		void setSalary(int a){
			salary = a;
		}
		int getSalary(){
			return salary;
		}
};
void classBasic() {
	cout << string(5, '=') << " CLASS BASIC" << endl;

	Book book;
	book.title = "Hello C++";
	book.author = "CPP";
	book.year = 1995;
	cout << book.title << " " << book.author << " " << book.year << endl;

	Dog dog;
	dog.bark(10);

	Car car1;
	Car car2("BMW", "X5");
	car1.print();
	car2.print();

	Company company;
	company.setSalary(2000);
	cout << company.getSalary() << endl;
}
int Basic() {
	helloWorld();
	ifElse();
	forLoop();
	whileLoop();
	switchCase();
	arrayBasic();
	classBasic();
	return 0;
}
