#pragma once
#include "Employee.h"

class FullTimeEmployee : public Employee {
   protected:
    void copy(const FullTimeEmployee& other);
    void free();
    unsigned workDays;
    double dailySalary;

   public:
    FullTimeEmployee() : Employee(), workDays(0), dailySalary(0) {}
    FullTimeEmployee(const char* _name, const unsigned _age,
                     const unsigned _workDays, const double _dailySalary)
        : Employee(_name, _age), workDays(_workDays), dailySalary(_dailySalary) {}
    FullTimeEmployee(const FullTimeEmployee& other);
    FullTimeEmployee& operator=(const FullTimeEmployee& other);
    ~FullTimeEmployee() override;

    double calculateSalary() const override;
};