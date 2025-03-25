#pragma once

class Person
{
private:
    int age;
    char* name = nullptr;

    void copy(int age, const char* name);
public:
    Person(int age, const char* name);
    Person(const Person& other); // copy constructor

    Person& operator=(const Person& other); // copy assignment operator

    const char* getName();

    ~Person();
};