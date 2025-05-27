#include "FullTimeEmployee.h"

void FullTimeEmployee::copy(const FullTimeEmployee& other) {
    this->dailySalary = other.dailySalary;
    this->workDays = other.workDays;
}

void FullTimeEmployee::free() {
    this->dailySalary = 0;
    this->workDays = 0;
}

FullTimeEmployee::FullTimeEmployee(const FullTimeEmployee& other) : Employee(other) {
    copy(other);
}

FullTimeEmployee& FullTimeEmployee::operator=(const FullTimeEmployee& other) {
    if(this != &other) {
        free();
        Employee::operator=(other);
        copy(other);
    }

    return *this;
}

FullTimeEmployee::~FullTimeEmployee() {
    free();
}

double FullTimeEmployee::calculateSalary() const {
    return this->dailySalary * this->workDays;
}
