#include <iostream>
#include "person.h"
#include "student.h"
#include "student_employee.h"
#include "member_list.h"

int main()
{
    Student student("Ivan", 21);
    Person p("Mariq", 22);
    Employee e("Vanq", 22);
    StudentEmployee se("Mitko", 23);
    Person* person = &se;

    StudentEmployee se2(se);

    MemberList list;
    list.addMember(&se);
    list.addMember(&student);
    list.addMember(&p);
    list.addMember(&e);

    std::cout << list << std::endl;

    // Example with cloning
    Person* cloned = person->clone();
    std::cout << *cloned;
}