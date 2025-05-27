#pragma once
#include "Employee.h"

class PartTimeEmployee : public Employee {
   protected:
    void copy(const PartTimeEmployee& other);
    void free();
    unsigned workHours;
    double hourlySalary;

   public:
    PartTimeEmployee() : Employee(), workHours(0), hourlySalary(0) {}
    PartTimeEmployee(const char* _name, const unsigned _age,
                     const unsigned _workHours, const double _hourlySalary)
        : Employee(_name, _age), workHours(_workHours), hourlySalary(_hourlySalary) {}
    PartTimeEmployee(const PartTimeEmployee& other);
    PartTimeEmployee& operator=(const PartTimeEmployee& other);
    ~PartTimeEmployee() override;

    double calculateSalary() const override;
};