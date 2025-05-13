#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "phone_number.hpp"
#include "..\..\Week04_Rule-0-3\person.h"

using namespace std;

class Register
{
private:
    map<PhoneNumber, const Person*> phoneBook;

public:
    bool add(const PhoneNumber& phone, const Person& person)
    {
        if (phoneBook.find(phone) != phoneBook.end())
        {
            return false; // Phone number already exists
        }

        phoneBook[phone] = &person;
        return true;
    }

    void add_with_exception(const PhoneNumber& phone, const Person& person)
    {
        if (phoneBook.find(phone) != phoneBook.end())
        {
            // Phone number already exists
            throw invalid_argument("Phone number already exists");
        }

        phoneBook[phone] = &person;
    }

    const Person* find(const PhoneNumber& phone) const
    {
        if (phoneBook.find(phone) != phoneBook.end())
        {
            return phoneBook.at(phone);
        }
        return nullptr;
    }

    int size() const
    {
        return phoneBook.size();
    }

    vector<PhoneNumber> get_all_numbers(const Person& person)
    {
        vector<PhoneNumber> result;

        for (std::map<PhoneNumber, const Person*>::iterator it = phoneBook.begin(); it!=phoneBook.end(); ++it)
            if (*(it->second) == person)
            {
                result.push_back(it->first);
            }
            
        return result;
    }    

};