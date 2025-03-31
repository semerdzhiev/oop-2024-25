#include <iostream>
#include <stdexcept>
#include <cstring>

class F1Driver
{
private:
    char* name;
    char* team;
    int points;

public:
    F1Driver(const char* name, const char* team, int points)
    {
        if (!name)
        {
            throw "Name is nullptr!";
        }
        if (!team)
        {
            throw "Team is nullptr!";
        }
        if (points < 0)
        {
            throw "Points are negative number";
        }

        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);

        try 
        {
            this->team = new char[strlen(team) + 1];
        } 
        catch (const std::bad_alloc& ba) 
        {
            delete[] this->name;
            throw ba;
        }
        strcpy(this->team, team);
    }

    F1Driver(const F1Driver& other) = delete;
    F1Driver& operator=(const F1Driver& other) = delete;

    ~F1Driver()
    {
        delete[] this->name;
        delete[] this->team;
    }
};

int main ()
{
    try
    {
        F1Driver norris("Lando Norris", "McLaren", 66);
    }
    catch (const char* stringException)
    {
        std::cerr << "String exception caught: " << stringException << std::endl;
    }
    catch (const std::bad_alloc& ba)
    {
        std::cerr << "Bad alloc exception caught: " << ba.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Something unexpected was caught" << std::endl; 
    }

    return 0;
}