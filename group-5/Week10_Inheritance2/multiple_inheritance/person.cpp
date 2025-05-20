#include "person.h"
#include <iostream>

Person::Person(std::string name, std::size_t age) 
    : age(age), name(name) 
{
    std::cout << "Person" << std::endl;
}

std::size_t Person::get_age() const
{
    return age;
}

std::string Person::get_name() const
{
    return name;
}

std::string Person::to_string() const
{
    std::string output = name;
    output += ", ";
    output += age;

    return output;
}

std::ostream& operator<<(std::ostream& os, const Person& person)
{
    // os << person.name << ", " << person.age;
    // os << person.to_string();

    person.print(os);
    return os;
}