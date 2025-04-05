#pragma once
#pragma warning (disable:4996)

#include <iostream>
#include <cstring>

class Author {
private:
    char* firstName = nullptr;
    char* lastName = nullptr;
    unsigned int age;
    char* email = nullptr;

public:
    Author(const char* firstName, const char* lastName, unsigned int age, const char* email);
    Author(const Author& other);
    Author& operator=(const Author& other);
    ~Author();

    const char* getFirstName() const;
    const char* getLastName() const;
    unsigned int getAge() const;
    const char* getEmail() const;

    friend std::ostream& operator<<(std::ostream& os, const Author& author);

private:
    void copyFrom(const Author& other);
    void free();
};