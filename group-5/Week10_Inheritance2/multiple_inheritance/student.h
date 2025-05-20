#pragma once
#include "person.h"

class Student : virtual public Person
{
private:
    double gpa;
    size_t year;

public:
    Student(std::string name, std::size_t age);

    virtual Person* clone() override;

    double get_gpa() const;
    std::size_t get_year() const;

    virtual std::string to_string() const override;
    virtual void print(std::ostream& os) const override;

    friend std::ostream& operator<<(std::ostream& os, const Student& student);
};
