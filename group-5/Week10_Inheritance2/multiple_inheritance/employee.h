#pragma once
#include "person.h"

class Employee : virtual public Person
{
private:
    std::size_t working_years;

public:
    Employee(std::string name, std::size_t age)
    : Person(name, age), working_years(0) 
    {
        std::cout << "Employee" << std::endl;
    }

    virtual Employee* clone(const Employee* person)
    {
        return new Employee(person->get_name(), person->get_age());
    }

    std::size_t get_working_years() const
    {
        return working_years;
    }

    virtual void print(std::ostream& os) const
    {
        Person::print(os);
        os << ", working_years: " << working_years;
    }

    friend std::ostream& operator<<(std::ostream& os, const Employee& employee)
    {
        employee.print(os);
        return os;
    }
};