#include "PartTimeEmployee.h"

void PartTimeEmployee::copy(const PartTimeEmployee& other) {
    this->hourlySalary = other.hourlySalary;
    this->workHours = other.workHours;
}

void PartTimeEmployee::free() {
    this->hourlySalary = 0;
    this->workHours = 0;
}

PartTimeEmployee::PartTimeEmployee(const PartTimeEmployee& other) : Employee(other) {
    copy(other);
}

PartTimeEmployee& PartTimeEmployee::operator=(const PartTimeEmployee& other) {
    if (this != &other) {
        free();
        Employee::operator=(other);
        copy(other);
    }

    return *this;
}

PartTimeEmployee::~PartTimeEmployee() {
    free();
}

double PartTimeEmployee::calculateSalary() const {
    return this->hourlySalary * this->workHours;
}
