#include "student.h"

Student::Student(std::string name, std::size_t age) 
: Person(name, age), gpa(6), year(0)
{
    if(age <= 2)
    {
        throw std::invalid_argument("Babies can't enroll uni!");
    }
    std::cout << "Student" << std::endl;
}

Person* Student::clone()
{
    // Creates a copy of the current object
    // It's then returned as a Person* pointer
    // But still supports Student functionality
    return new Student(*this);
}

double Student::get_gpa() const
{
    return gpa;
}    

std::size_t Student::get_year() const
{
    return year;
}

std::string Student::to_string() const 
{
    std::string output = Person::to_string();
    output = output + ", gpa: ";
    output += gpa;
    output += ", year: ";
    output += year;

    return output;
}

void Student::print(std::ostream& os) const
{
    Person::print(os);
    os << ", gpa: " << gpa
        << ", year: " << year;
}

std::ostream& operator<<(std::ostream& os, const Student& student)
{
    // os << student.to_string();
    student.print(os);
    return os;
}