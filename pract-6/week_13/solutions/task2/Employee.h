#pragma once
#include <string>

class Employee {
   protected:
    void copy(const Employee& other);
    void free();
    char* name;
    unsigned age;

   public:
    Employee() : name(nullptr), age(0) {}
    Employee(const char* _name, unsigned _age);
    Employee(const Employee& other);
    Employee& operator=(const Employee& other);
    virtual ~Employee();
    virtual double calculateSalary() const = 0;
};