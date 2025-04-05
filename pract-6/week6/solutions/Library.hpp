#pragma once

#include "Book.hpp"

class Library {
private:
    struct BookCountPair {
        Book* book;
        unsigned int count;

        BookCountPair(Book* book, unsigned int count) {
            this->book = new Book(*book);
            this->count = count;
        }

        ~BookCountPair() {
            delete book;
        }

        BookCountPair(const BookCountPair& other) {
            book = new Book(*other.book);
            count = other.count;
        }

        BookCountPair& operator=(const BookCountPair& other) {
            if (this != &other) {
                delete book;
                book = new Book(*other.book);
                count = other.count;
            }
            return *this;
        }
    };

    BookCountPair** books;
    unsigned int booksCount;

public:
    Library();
    Library(const Library& other);
    Library& operator=(const Library& other);
    ~Library();

    //void addBook(Book* book, unsigned int count);
    unsigned int operator[](const char* title) const;
    bool isBookAvailable(const char* title) const;
    void sortBooksAlphabetically();
    Book** getBooksByAuthor(const Author& author, unsigned int& outCount) const;

private:
    void copyFrom(const Library& other);
    void free();
};
