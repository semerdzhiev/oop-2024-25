#pragma once
#include <iostream>
#include <cstring>
using namespace std;

const int MAX_NAME_SIZE = 100;

struct Student{
    int age;
    float gpa;
    char name[100];
};
    
void readStudent(Student& student);

void printStudent(const Student& student);

void saveToFile(const Student* students, size_t count, const char* filename);

void saveToFile(const Student* students, size_t count, std::fstream& file);

Student* readFromFile(const char* filename, size_t & count);