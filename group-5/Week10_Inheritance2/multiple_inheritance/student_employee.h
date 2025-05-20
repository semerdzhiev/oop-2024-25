#pragma once
#include "person.h"
#include "student.h"
#include "employee.h"

/*
Student -> Person
Employee -> Person
StudentEmployee -> Student, Employee
*/

class StudentEmployee : public Student, public Employee
{
public:
    StudentEmployee(std::string name, std::size_t age)
        : Student(name, age), Employee(name, age), Person(name, age) 
    {
        std::cout << "StudentEmployee" << std::endl;        
    }

    virtual Person* clone() override
    {
        return new StudentEmployee(*this);
    }

    virtual void print(std::ostream& os) const override
    {
        Student::print(os);
        os << ", working_years: " << get_working_years();
    }
};