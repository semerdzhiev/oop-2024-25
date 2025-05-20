#pragma once
#include <iostream>

class Person
{
private:
    std::size_t age;
    std::string name;

public:
    Person(std::string name, std::size_t age = 0);

    std::size_t get_age() const;
    std::string get_name() const;

    virtual Person* clone()
    {
        // creates a copy of of the current object
        // calls copy constructor (created by default)
        return new Person(*this);
    }

    virtual std::string to_string() const;

    // Better way
    virtual void print(std::ostream& os) const
    {
        os << name << ", " << age;
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& person);
};