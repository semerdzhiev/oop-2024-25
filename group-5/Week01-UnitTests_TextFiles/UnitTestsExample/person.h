#pragma once
#include <cstring>

const int MAX_NAME_SIZE = 100;

struct Person {
    bool gender;
    char name[MAX_NAME_SIZE];
    int age;
};

Person createPerson(bool gender, int age, const char* name);

bool isMature(const Person& p);
bool isOlder(const Person& p1, const Person& p2);