#include <iostream>
#include <vector>
#include <map>
#include "phone_number.hpp"
#include "..\..\Week04_Rule-0-3\person.h"
#include "register.hpp"

using namespace std;

std::ostream& operator<<(std::ostream& os, const PhoneNumber& num)
{
    os << num.getNumber();
    return os;
}

int main()
{
    Person ivan(20, "Ivan");
    Person mariq(19, "Mariq");

    Register reg;

    reg.add("+359887766554", ivan);
    reg.add("+359887766556", ivan);
    reg.add("+359887766555", mariq);

    try
    {
        PhoneNumber num("-359887766554");
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }

    vector<PhoneNumber> numbers = reg.get_all_numbers(ivan);
    for (size_t i = 0; i < numbers.size(); i++)
    {
        cout << numbers[i] << endl;
    }
    
}