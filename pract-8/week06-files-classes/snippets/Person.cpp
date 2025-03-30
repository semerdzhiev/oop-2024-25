#include "Person.hpp"


void Person::freeMemory() {
    delete[] firstName;
    delete[] lastName;
    firstName = nullptr;
    lastName = nullptr;
}


void Person::copy(const Person& other) {
    firstName = new char[std::strlen(other.firstName) + 1];
    std::strcpy(firstName, other.firstName);

    lastName = new char[std::strlen(other.lastName) + 1];
    std::strcpy(lastName, other.lastName);

    age = other.age;
}

Person::Person(const char* firstName, const char* lastName, unsigned age) : age(age) {
    if (firstName == nullptr || lastName == nullptr) {
        throw std::invalid_argument("Невалиден указател към низ!");
    }
    this->firstName = new char[std::strlen(firstName) + 1];
    std::strcpy(this->firstName, firstName);

    this->lastName = new char[std::strlen(lastName) + 1];
    std::strcpy(this->lastName, lastName);
}

Person::Person(const Person& other) {
    copy(other);
}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        freeMemory();
        copy(other);
    }
    return *this;
}

Person::~Person() {
    freeMemory();
}

void Person::serialize(std::ostream& os) const {
    os << firstName << "\n" << lastName << "\n" << age << "\n";
}

void Person::deserialize(std::istream& is) {
    const int bufferSize = 100;
    char buffer[bufferSize + 1];

    is.getline(buffer, bufferSize + 1);
    delete[] firstName;
    firstName = new char[std::strlen(buffer) + 1];
    std::strcpy(firstName, buffer);

    is.getline(buffer, bufferSize + 1);
    delete[] lastName;
    lastName = new char[std::strlen(buffer) + 1];
    std::strcpy(lastName, buffer);

    is >> age;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Person::print() const {
    std::cout << firstName << " " << lastName << " " << age << std::endl;
}

void Person::serializeBinary(std::ostream& os) const {
    // Записваме дължината на firstName
    unsigned int len = std::strlen(firstName) + 1;
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    os.write(firstName, len);

    // Записваме дължинатa на lastName
    len = std::strlen(lastName) + 1;
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    os.write(lastName, len);

    // Записваме възрастта
    os.write(reinterpret_cast<const char*>(&age), sizeof(age));
}

void Person::deserializeBinary(std::istream& is) {
    unsigned int len = 0;

    // Четене на firstName
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    delete[] firstName;
    firstName = new char[len];
    is.read(firstName, len);

    // Четене на lastName
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    delete[] lastName;
    lastName = new char[len];
    is.read(lastName, len);

    // Четене на възрастта
    is.read(reinterpret_cast<char*>(&age), sizeof(age));
}