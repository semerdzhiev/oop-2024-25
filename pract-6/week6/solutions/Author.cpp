#include "Author.hpp"

Author::Author(const char* firstName, const char* lastName, unsigned int age, const char* email) {
    if (!firstName || !lastName || !email)
        throw std::invalid_argument("Null pointer passed to Author constructor");

    if (age < 0)
        throw std::invalid_argument("Age cannot be less than zero!");

    this->firstName = new (std::nothrow) char[strlen(firstName) + 1];
    this->lastName = new (std::nothrow) char[strlen(lastName) + 1];
    this->email = new (std::nothrow) char[strlen(email) + 1];
    if (!firstName || !lastName || !email) {
        delete[] firstName;
        delete[] lastName;
        delete[] email;
        throw std::bad_alloc();
    }
    strcpy(this->firstName, firstName);
    strcpy(this->lastName, lastName);
    strcpy(this->email, email);

    this->age = age;
}

Author::Author(const Author& other) {
    copyFrom(other);
}

Author& Author::operator=(const Author& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Author::~Author() {
    free();
}

const char* Author::getFirstName() const { return firstName; }
const char* Author::getLastName() const { return lastName; }
unsigned int Author::getAge() const { return age; }
const char* Author::getEmail() const { return email; }

std::ostream& operator<<(std::ostream& os, const Author& author) {
    os << author.firstName << " " << author.lastName << " (" << author.age << ") - " << author.email;
    return os;
}

void Author::copyFrom(const Author& other) {
    firstName = new (std::nothrow) char[strlen(other.firstName) + 1];
    lastName = new (std::nothrow) char[strlen(other.lastName) + 1];
    email = new (std::nothrow) char[strlen(other.email) + 1];
    if (!firstName || !lastName || !email) {
        delete[] firstName;
        delete[] lastName;
        delete[] email;
        throw std::bad_alloc();
    }
    strcpy(firstName, other.firstName);
    strcpy(lastName, other.lastName);
    strcpy(email, other.email);

    age = other.age;
}

void Author::free() {
    delete[] firstName;
    delete[] lastName;
    delete[] email;

    firstName = nullptr;
    lastName = nullptr;
    email = nullptr;
}