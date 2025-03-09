#include <iostream>

#pragma warning (disable:4996)

struct  Person {
public:
	Person()
		: name(nullptr), age(0) {}

	Person(const char* name, int age)
		: age(age) { // Първото age е член данната на класа
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->age = age;
	}

	Person(const Person& other) {
		copyFrom(other);
	}

	Person& operator=(const Person& other) {
		if (this != &other) {
			delete[] name;
			copyFrom(other);
		}

		return *this;
	}

	~Person() {
		delete[] name;
	}

private:
	void copyFrom(const Person& other) {
		int nameLength = strlen(other.name);
		name = new char[nameLength + 1];
		strcpy(name, other.name);

		age = other.age;
	}

//public: // for testing in main
	char* name;
	int age;
};

int main() {
	Person p1("Ivan", 3);
	Person p2("Georgi", 5);

	p1 = p1; // !

	//cout << p1.name << endl;
	//cout << p2.name << endl;
	//cout << endl;
	//strcpy(p2.name, "Niki");

	//cout << p1.name << endl;
	//cout << p2.name << endl;
}