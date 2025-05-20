#include <iostream>

class Base
{
    int* x;
public:
    Base() : x(new int(0)) // Constructor
    {
        std::cout << "Base constructor called" << std::endl;
    }

    virtual const char* print()
    {
        return "Base";
    }
    
    virtual ~Base() // Virtual destructor
    {
        std::cout << "Base destructor called" << std::endl;
        delete x;
    }
};

class Derived2 : public Base
{
    int* y;
public:
    Derived2() : y(new int(0)) // Constructor
    {
        std::cout << "Derived2 constructor called" << std::endl;
    }

    virtual const char* print()
    {
        return "Derived2";
    }
    
    ~Derived2() // Virtual destructor
    {
        std::cout << "Derived2 destructor called" << std::endl;
        delete y;
    }
};

void visualize(Base* b)
{
    std::cout << b->print() << std::endl;
}

void visualize_der2(Derived2* b)
{
    std::cout << b->print() << std::endl;
}

int main()
{
    // Derived2 der;
    // // Derived* p_der = &der;
    // Base* p_base = &der;

    // visualize(&der);
    // visualize_der2(&der);

    Derived2* new_der = new Derived2;
    Base* p_base2 = new_der;

    delete new_der;
}