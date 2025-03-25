#include "mystring.h"
#include <iostream>
#include <cstring>

using namespace std;

char* MyString::allocate(size_t size)
{
    char* temp = new (std::nothrow) char[size];

    if (temp == nullptr)
    {
        cerr << "Couldn't allocate memory" << endl;
        return nullptr;
    }

    return temp;
}

MyString::MyString() 
{
    MyString(capacity);
    // content = allocate(capacity);
    // content[0] = '\0';
}

MyString::MyString(size_t capacity) : capacity(capacity)
{
    content = allocate(capacity);
    content[0] = '\0';
}

void MyString::resize(size_t capacity)
{
    char* temp = allocate(capacity);

    if (content != nullptr)
    {
        strncpy(temp, content, capacity);
        delete[] content;
    }
    else if (capacity > 0)
    {
        temp[0] = '\0';
    }

    content = temp;
    this->capacity = capacity;
}

void MyString::copy(const char* other) 
{
    size_t len = strlen(other);

    if (capacity < len + 1)
    {
        resize(len+1);
    }

    strcpy(content, other);
    size = len;
}

MyString::MyString(const MyString& other) : capacity(other.capacity)
{
    copy(other.content);   
}

MyString::MyString(const char* other)
{
    content = allocate(capacity);
    copy(other);
}

MyString::MyString(size_t capacity, const MyString& other) 
    : capacity(capacity)
{
    content = allocate(capacity);
    copy(other.content);
}

MyString& MyString::operator=(const MyString& other)
{
    if (this == &other)
    {
        return *this;
    }

    copy(other.content);
}

MyString MyString::operator+(const MyString& other)
{
    size_t new_capacity = other.size + size + 1;
    MyString res(new_capacity, content);

    strcpy((res.content + size), other.content);
    return res;
}

const char* MyString::str() const
{
    return content;
}

MyString::~MyString()
{
    delete[] content;
}