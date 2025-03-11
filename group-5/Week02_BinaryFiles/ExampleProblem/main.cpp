#include <iostream>
#include "student.h"
using namespace std;


int main()
{
    // size_t count;
    // cout << "Student count: ";
    // cin >> count;

    // Student* students = new Student[count];

    // for (size_t i = 0; i < count; i++)
    // {
    //     readStudent(students[i]);
    // }
    
    // for (size_t i = 0; i < count; i++)
    // {
    //     cout << "Student " << i << endl;
    //     printStudent(students[i]);
    // }

    // saveToFile(students, count, "students.dat");
    
    size_t count;
    Student* students = readFromFile("students.dat", count);

    for (size_t i = 0; i < count; i++)
    {
        cout << "Student " << i << endl;
        printStudent(students[i]);
    }

    delete[] students;
}