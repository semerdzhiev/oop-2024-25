#ifndef EMPLOYEE_HPP_
#define EMPLOYEE_HPP_

#include <cstring>
#include <iostream>

struct Employee {
    char name[50];
    char position[50];
    double salary;
    int workExperience;

    Employee();
    Employee(const char* n, const char* pos, double sal, int exp);
    double calculateBonus() const;
    void print() const;
};

#endif // EMPLOYEE_HPP_