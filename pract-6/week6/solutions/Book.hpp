#pragma once

#include "Author.hpp"

class Book {
private:
    char* title = nullptr;
    Author** authors = nullptr;
    unsigned int authorCount;
    double price;
    char* text = nullptr;

public:
    Book(const char* title, Author** authors, unsigned int authorCount, double price, const char* text);
    Book(const Book& other);
    Book& operator=(const Book& other);
    ~Book();

    const char* getTitle() const;
    double getPrice() const;
    bool hasAuthor(const char* firstName, const char* lastName) const;
    void changePrice(double newPrice);
    void printText() const;

    friend std::ostream& operator<<(std::ostream& os, const Book& book);

private:
    void copyFrom(const Book& other);
    void free();
};
