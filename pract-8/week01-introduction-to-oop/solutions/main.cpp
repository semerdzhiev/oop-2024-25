#include <iostream>
#include <cstring>

#include "ComplexNumber.hpp"
#include "Time.hpp"
#include "Employee.hpp"

int main() {

    // Task 01: ComplexNumber
    std::cout << "Task 1: ComplexNumber" << std::endl;
    ComplexNumber c1(3.0, 2.0);
    ComplexNumber c2(1.0, 7.0);
    ComplexNumber sum = c1.add(c2);
    ComplexNumber diff = c1.subtract(c2);
    ComplexNumber prod = c1.multiply(c2);

    std::cout << "c1 = "; c1.print();
    std::cout << "c2 = "; c2.print();
    std::cout << "Sum: "; sum.print();
    std::cout << "Difference: "; diff.print();
    std::cout << "Product: "; prod.print();
    std::cout << std::endl;

    // Task 02: Time
    std::cout << "Task 2: Time" << std::endl;
    Time t1(10, 45, 30);
    Time t2(11, 0, 15);
    std::cout << "Initial time t1: "; t1.print();
    t1.addSeconds(50);
    std::cout << "After adding 50 seconds: "; t1.print();
    t1.addMinutes(20);
    std::cout << "After adding 20 minutes: "; t1.print();
    t1.addHours(2);
    std::cout << "After adding 2 hours: "; t1.print();
    std::cout << "Time t2: "; t2.print();
    std::cout << "Comparison result (t1 vs t2): " << t1.compare(t2) << std::endl;
    std::cout << "Comparison result (t2 vs t1): " << t2.compare(t1) << std::endl;
    std::cout << "Comparison result (t1 vs t1): " << t1.compare(t1) << std::endl;
    std::cout << std::endl;

    // Task 03: Employee
    std::cout << "Task 3: Employee" << std::endl;
    Employee emp("Ivan Ivanov", "Software Engineer", 3000.0, 5);
    emp.print();
    std::cout << std::endl;

    return 0;
}
