#include "Book.hpp"

Book::Book(const char* title, Author** authors, unsigned int authorCount, double price, const char* text) {
    if (!title || !text || !authors)
        throw std::invalid_argument("Null pointer passed to Book constructor");

    this->title = new (std::nothrow) char[strlen(title) + 1];
    this->text = new (std::nothrow) char[strlen(text) + 1];
    this->authors = new (std::nothrow) Author*[authorCount];

    if (!this->title || !this->text || !this->authors) {
        delete[] this->title;
        delete[] this->text;
        delete[] this->authors;
        throw std::bad_alloc();
    }

    this->authorCount = authorCount;
    for (unsigned int i = 0; i < authorCount; i++) {
        this->authors[i] = new (std::nothrow) Author(*authors[i]);
        if (!this->authors[i]) {
            for (unsigned int j = 0; j < i; j++)
                delete this->authors[j];

            delete[] this->authors;
            delete[] this->title;
            delete[] this->text;
            throw std::bad_alloc();
        }
    }

    strcpy(this->title, title);
    strcpy(this->text, text);

    this->price = price;
}

Book::Book(const Book& other) {
    copyFrom(other);
}

Book& Book::operator=(const Book& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Book::~Book() {
    free();
}

const char* Book::getTitle() const { return title; }
double Book::getPrice() const { return price; }

bool Book::hasAuthor(const char* firstName, const char* lastName) const {
    for (unsigned int i = 0; i < authorCount; i++) {
        if (strcmp(authors[i]->getFirstName(), firstName) == 0 && strcmp(authors[i]->getLastName(), lastName) == 0) {
            return true;
        }
    }
    return false;
}

void Book::changePrice(double newPrice) { price = newPrice; }
void Book::printText() const { std::cout << text << std::endl; }

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "Title: " << book.title << ", Price: " << book.price;
    return os;
}

void Book::copyFrom(const Book& other) {
    title = new (std::nothrow) char[strlen(other.title) + 1];
    text = new (std::nothrow) char[strlen(other.text) + 1];
    authors = new (std::nothrow) Author * [other.authorCount];

    if (!title || !text || !authors) {
        delete[] title;
        delete[] text;
        delete[] authors;
        throw std::bad_alloc();
    }

    authorCount = other.authorCount;
    for (unsigned int i = 0; i < authorCount; i++) {
        authors[i] = new (std::nothrow) Author(*other.authors[i]);
        if (!authors[i]) {
            for (unsigned int j = 0; j < i; j++)
                delete authors[j];

            delete[] authors;
            delete[] title;
            delete[] text;
            throw std::bad_alloc();
        }
    }

    strcpy(title, other.title);
    strcpy(text, other.text);

    price = other.price;
}

void Book::free() {
    delete[] title;
    delete[] text;
    for (unsigned int i = 0; i < authorCount; i++)
        delete authors[i];
    delete[] authors;

    title = nullptr;
    text = nullptr;
    authors = nullptr;
}
