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
int Basic() {
	helloWorld();
	ifElse();
	forLoop();
	whileLoop();
	switchCase();
	arrayBasic();
	return 0;
}
