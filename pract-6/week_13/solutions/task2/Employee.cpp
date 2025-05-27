#include "Employee.h"
#include <cstring>

void Employee::copy(const Employee& other) {
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    this->age = other.age;
}

void Employee::free() {
    delete[] this->name;
    this->name = nullptr;
    this->age = 0;
}

Employee::Employee(const char* _name, const unsigned _age) : age(_age) {
    this->name = new char[strlen(_name) + 1];
    strcpy(this->name, _name);
}

Employee::Employee(const Employee& other) {
    copy(other);
}

Employee& Employee::operator=(const Employee& other) {
    if(this != &other) {
        free();
        copy(other);
    }
    return *this;
}

Employee::~Employee() {
    free();
}
