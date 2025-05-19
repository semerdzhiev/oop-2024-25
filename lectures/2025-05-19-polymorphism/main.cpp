#include <iostream>
#include <sstream>
#include <string>

class type {
public:
    virtual std::string to_string() const = 0;
    virtual std::string name() const = 0;
    virtual ~type() { };
};

class integer_type : public type {
    int value;

public:
    integer_type(int value)
        : value(value)
    {
    }

    integer_type(std::string str) { value = std::stoi(str); }

    virtual std::string to_string() const override
    {
        return std::to_string(value);
    }

    virtual std::string name() const override { return "integer"; }
};

class date_type : public type {
    int year;
    int month;
    int day;

public:
    date_type(int year, int month, int day)
        : year(year)
        , month(month)
        , day(day)
    {
    }

    date_type(std::string str)
    {
        bool check = str.size() == 10 && std::isdigit(str[0])
            && std::isdigit(str[1]) && std::isdigit(str[2])
            && std::isdigit(str[3]) && str[4] == '-' && std::isdigit(str[5])
            && std::isdigit(str[6]) && str[7] == '-' && std::isdigit(str[8])
            && std::isdigit(str[9]);

        if (!check)
            throw std::invalid_argument("Not a valid representation of a date");

        char c;
        std::istringstream input(str);
        input >> year >> c >> month >> c >> day;
    }

    virtual std::string to_string() const override
    {
        std::ostringstream str;
        str << year << '-' << month << '-' << day;
        return str.str();
    }

    virtual std::string name() const override { return "date"; }
};

//---------------------------------------------------

class type_factory {
public:
    virtual type* create() = 0;
    virtual ~type_factory() { }
};

class stdin_type_factory : public type_factory {
public:
    virtual type* create() override
    {
        std::string name;
        std::string value;
        std::cout << "Enter type info: ";

        // e.g.
        // date 2025-10-20
        // number 564
        std::cin >> name >> value;

        if (name == "integer") {
            return new integer_type(value);
        } else if (name == "date") {
            return new date_type(value);
        } else {
            throw std::runtime_error("Incorrect type");
        }
    }
};

class random_type_factory : public type_factory {
public:
    virtual type* create() override
    {
        if (std::rand() % 2 == 0) {
            return new integer_type(std::rand());
        } else {
            return new date_type(
                1900 + std::rand() % 2000,
                1 + std::rand() % 12,
                1 + std::rand() % 28
            );
        }
    }
};

class choose_your_input {
public:
    type_factory* create()
    {
        char choice;
        std::cout << "Choose how you want to enter your data "
                     "(r)andom, (s)tdin: ";
        std::cin >> choice;

        switch (choice) {
            case 'r':
                return new random_type_factory();
            case 's':
                return new stdin_type_factory();
            default:
                throw std::runtime_error("Incorrect input method");
        }
    }
};

void print_type_info(type& something)
{
    std::cout << "\nType information" << std::endl;
    std::cout << "  - name: " << typeid(something).name() << std::endl;
    std::cout << "  - hash: " << typeid(something).hash_code() << std::endl;
    std::cout << "  - is it an integer_type: "
              << (typeid(something) == typeid(integer_type) ? "yes" : "no")
              << std::endl;
    std::cout << "  - is it a date_type: "
              << (typeid(something) == typeid(date_type) ? "yes" : "no")
              << std::endl;
}

void try_to_cast_by_ref(type& something)
{
    std::cout << "\nTrying to cast the object (by reference):\n";

    try {
        std::cout << "  - to integral_type ";
        integer_type& iref = dynamic_cast<integer_type&>(something);
        std::cout << "OK" << std::endl;
    } catch (std::bad_cast&) {
        std::cout << "Failed" << std::endl;
    }

    try {
        std::cout << "  - to date_type: ";
        date_type& dref = dynamic_cast<date_type&>(something);
        std::cout << "OK" << std::endl;
    } catch (std::bad_cast&) {
        std::cout << "Failed" << std::endl;
    }
}

void try_to_cast_by_ref(type* something)
{
    std::cout << "\nTrying to cast the object (by pointer):\n";

    std::cout << "  - to integral_type: ";
    integer_type* int_ptr = dynamic_cast<integer_type*>(something);
    std::cout << (int_ptr ? "OK" : "Failed") << std::endl;

    std::cout << "  - to date_type: ";
    date_type* date_ptr = dynamic_cast<date_type*>(something);
    std::cout << (date_ptr ? "OK" : "Failed") << std::endl;
}

int main()
{
    try {
        choose_your_input cyi;

        type_factory* tf = cyi.create();
        type* something = tf->create();

        std::cout << "\nYou just entered a value of type " << something->name()
                  << " and its value is " << something->to_string()
                  << std::endl;

        print_type_info(*something);

        try_to_cast_by_ref(*something);
        try_to_cast_by_ref(something);

        delete something;
        delete tf;

    } catch (std::exception& e) {
        std::cout << "Something happened: " << e.what() << std::endl;
    }
}
