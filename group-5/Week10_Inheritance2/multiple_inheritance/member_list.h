#pragma once
#include "person.h"
#include <vector>
#include <iostream>

class MemberList
{
private:
    std::vector<Person*> members;
    // Person** members;
public:
    MemberList() {}

    void addMember(Person* person)
    {
        members.push_back(person);
    }

    const Person* get_member(size_t pos) const
    {
        return members[pos];
    }

    size_t get_size() const
    {
        return members.size();
    }

    friend std::ostream& operator<<(std::ostream& os, const MemberList& list)
    {
        for (size_t i = 0; i < list.get_size(); i++)
        {
            os << *list.get_member(i) << "\n";
        }
        return os;
    }
};