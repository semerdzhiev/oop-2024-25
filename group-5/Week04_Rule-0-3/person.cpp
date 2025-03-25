#include <iostream>
#include <cstring>
#include "person.h"

using namespace std;

void Person::copy(int age, const char* name) 
{
	this->age = age;
	
	this->name = new (std::nothrow) char[strlen(name) + 1];
	if (this->name == nullptr)
	{
		cerr << "Couldn't allocate memory" << endl;
		return;
	}
	strcpy(this->name, name);
}

Person::Person(int age, const char* name) : age(age)
{
	if (name == nullptr)
	{
		cerr << "Invalid name" << endl;
		return;
	}
	copy(age, name);
}

Person::Person(const Person& other)
{
	copy(other.age, other.name);
}

Person::~Person()
{
	delete[] name;
}

Person& Person::operator=(const Person& other)
{
	if (this == &other)
	{
		return *this;
	}

	delete[] name;
	copy(other.age, other.name);

	return *this;
}

const char* Person::getName()
{
	return name;
}