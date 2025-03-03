#include "person.h"

Person createPerson(bool gender, int age, const char* name)
{
    Person p;

    strncpy(p.name, name, MAX_NAME_SIZE);
    p.gender = gender;
    p.age = age;

    return p;
}

bool isMature(const Person& p)
{
    return p.age > 18;
}

bool isOlder(const Person& p1, const Person& p2)
{
    return p1.age > p2.age;
}