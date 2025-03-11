#include "student.h"
#include<fstream>

using namespace std;

void readStudent(Student& student)
{
    cout << "Age: ";
    cin >> student.age;

    cout << "gpa: ";
    cin >> student.gpa;
    
    cout << "Name: ";
    
    char tmp[MAX_NAME_SIZE];
    cin >> tmp;
    strncpy(student.name, tmp, MAX_NAME_SIZE);
}

void printStudent(const Student& student)
{
    cout << "Age: " << student.age << endl;
    cout << "GPA: " << student.gpa << endl;
    cout << "Name: " << student.name << endl;
}

void saveToFile(const Student* students, size_t count, const char* filename)
{
    std::fstream file(filename, ios::binary | ios::out);

    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;

        return;
    }

    saveToFile(students, count, file);

    file.close();
}

void saveToFile(const Student* students, size_t count, std::fstream& file)
{
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    for (size_t i = 0; i < count; i++)
    {
        file.write(reinterpret_cast<const char*>(&(students[i])), sizeof(students[i]));
    }
}


Student* readFromFile(const char* filename, size_t& count)
{
    std::fstream file(filename, ios::binary | ios::in);

    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;

        return nullptr;
    }

    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    Student* students = new Student[count];
    for (size_t i = 0; i < count; i++)
    {
        file.read(reinterpret_cast<char*>(&(students[i])), sizeof(students[i]));
    }
    
    return students;
}