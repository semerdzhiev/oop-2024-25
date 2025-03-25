#pragma once
#include <cstddef>

class MyString
{
private:
    char* content = nullptr;
    size_t capacity = 10;
    size_t size = 0;

    void copy(const char* other);
    char* allocate(size_t size);
    void resize(size_t new_size);
public:
    MyString();
    MyString(size_t capacity);
    MyString(const char* content);
    MyString(const MyString& other);
    MyString(size_t capacity, const MyString& content);

    MyString& operator=(const MyString& other);

    MyString operator+(const MyString& other);
    // MyString& operator+=(const MyString& other);

    const char* str() const;
    // char& operator[](size_t idx);
    // char operator[](size_t idx) const;

    // void print() const;

    ~MyString();
};

