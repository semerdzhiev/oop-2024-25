#include<iostream>
#include "mystring.h"

using namespace std;

int main()
{
    MyString str1("aba");
    MyString str2("com");

    MyString res = str1 + str2;

    cout << res.str() << endl;
}