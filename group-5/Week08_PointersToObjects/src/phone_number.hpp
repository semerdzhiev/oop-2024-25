#pragma once
#include <iostream>
#include <cstring>

using namespace std;

class PhoneNumber
{
public:
    static const int SIZE = 13;
    
private:
    char number[SIZE+1];

    void copy(const char* num)
    {
        strncpy(number, num, SIZE);
        number[SIZE] = '\0';
    }
public:
    PhoneNumber(const char* num = "+359000000000")
    {
        if(num[0] != '+')
        {
            std::cerr << "Invalid phone number format. Must start with '+'.\n";
            throw invalid_argument("Invalid phone number format");
        }
        for (size_t i = 1; i < SIZE; i++)
        {
            if(!isdigit(num[i]))
            {
                std::cerr << "Invalid phone number format. Must contain only digits after '+'.\n";
                throw invalid_argument("Invalid phone number format");
            }
        }
        
        copy(num);
    }

    PhoneNumber(const PhoneNumber& other)
    {
        copy(other.number);
    }

    PhoneNumber& operator=(const PhoneNumber& other)
    {
        if (this != &other)
        {
            copy(other.number);
        }
        return *this;
    }

    void print() const
    {
        std::cout << number << std::endl;
    }

    const char* getNumber() const
    {
        return number;
    }

    bool operator<(const PhoneNumber& other) const
    {
        return strcmp(number, other.number) < 0;
    }

    // friend std::ostream& operator<<(std::ostream& os, const PhoneNumber& num)
    // {
    //     os << num.number;
    //     return os;
    // }
};