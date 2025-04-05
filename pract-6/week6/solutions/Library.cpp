#include "Library.hpp"

#include <cstring>
#include <algorithm>

Library::Library() : books(nullptr), booksCount(0) {}

Library::Library(const Library& other) {
    copyFrom(other);
}

Library& Library::operator=(const Library& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Library::~Library() {
    free();
}

// Add book method (not in the requirements) - resizes every time a book is added (not optimal).
// (You can try to implement resize method with a capacity that multiplies by two..)

//void Library::addBook(Book* book, unsigned int count) {
//    if (!book) ........
// 
//    BookCountPair** newBooks = new BookCountPair*[booksCount + 1];
//
//    for (unsigned int i = 0; i < booksCount; i++) {
//        newBooks[i] = books[i];
//    }
//
//    newBooks[booksCount] = new BookCountPair(book, count);
//    delete[] books;
//    books = newBooks;
//    booksCount++;
//}

unsigned int Library::operator[](const char* title) const {
    for (unsigned int i = 0; i < booksCount; i++) {
        if (strcmp(books[i]->book->getTitle(), title) == 0) {
            return books[i]->count;
        }
    }
    return 0;
}

bool Library::isBookAvailable(const char* title) const {
    for (unsigned int i = 0; i < booksCount; i++) {
        if (strcmp(books[i]->book->getTitle(), title) == 0 && books[i]->count > 0) {
            return true;
        }
    }
    return false;
}

void Library::sortBooksAlphabetically() {
    bool swapped;
    for (unsigned int i = 0; i < booksCount - 1; i++) {
        swapped = false;
        for (unsigned int j = 0; j < booksCount - i - 1; j++) {
            if (strcmp(books[j]->book->getTitle(), books[j + 1]->book->getTitle()) > 0) {
                BookCountPair* temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

Book** Library::getBooksByAuthor(const Author& author, unsigned int& outCount) const {
    outCount = 0;

    for (unsigned int i = 0; i < booksCount; i++) {
        if (books[i]->book->hasAuthor(author.getFirstName(), author.getLastName()))
            outCount++;
    }

    if (outCount == 0) return nullptr;

    Book** result = new Book*[outCount];

    unsigned int index = 0;
    for (unsigned int i = 0; i < booksCount; i++) {
        if (books[i]->book->hasAuthor(author.getFirstName(), author.getLastName())) {
            result[index] = new Book(*books[i]->book);

            if (!result[index]) {
                for (unsigned int j = 0; j < index; j++)
                    delete result[j];

                delete[] result;
                throw std::bad_alloc();
            }
            index++;
        }
    }

    return result;
}

void Library::copyFrom(const Library& other) {
    booksCount = other.booksCount;
    books = new BookCountPair * [booksCount];

    for (unsigned int i = 0; i < booksCount; i++) {
        books[i] = new BookCountPair(other.books[i]->book, other.books[i]->count);
        if (!books[i]) {
            for (unsigned int j = 0; j < i; j++)
                delete books[j];

            delete[] books;
            throw std::bad_alloc();
        }
    }
}

void Library::free() {
    for (unsigned int i = 0; i < booksCount; i++) {
        delete books[i];
    }
    delete[] books;
    books = nullptr;
    booksCount = 0;
}
