#pragma once
#include <iostream>

class Money
{
private:
    unsigned int levs;
    unsigned int stotinkas;
// bool isEqual = a == b
// Money result = Money(1, 20) + Money(2, 30)
// result += Money(1, 20)
// Money(1, 20) + 5
// std::cin >> money
// 2 + Money(2, 50)
public:
    Money(const unsigned int levs, const unsigned int stotinkas);

    bool operator == (const Money& other) const;
    bool operator != (const Money& other) const;
    bool operator < (const Money& other) const;
    bool operator >= (const Money& other) const;

    Money& operator += (const Money& other);
    Money operator + (const Money& other) const;
    
    Money operator + (const unsigned int levs) const;
    // Money operator + (double money) const;

    Money operator ++ (int); // x++
    Money& operator ++ (); // ++x

    friend Money operator + (const unsigned int levs, const Money& money);

    friend std::ostream& operator << (std::ostream& out, const Money& money);
    friend std::istream& operator >> (std::istream& in, Money& money);
};