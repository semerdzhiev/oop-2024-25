#ifndef PERSON_HPP_
#define PERSON_HPP_

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <limits>

class Person {
private:	
	char* firstName;
	char* lastName;
	unsigned age;
	
	void freeMemory();
	void copy(const Person& other);
public:
	Person(const char* firstName = "", const char* lastName = "", unsigned age = 0);
	Person(const Person& other);
	Person& operator=(const Person& other);
	~Person();

	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);

    void serializeBinary(std::ostream& os) const;
    void deserializeBinary(std::istream& is);

    void print() const;
};

#endif // !PERSON_HPP_
