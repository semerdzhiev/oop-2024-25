#pragma once

#include <iostream>
#include <cstring>

#pragma warning (disable:4996)

class Beer {
private:
    char* name;
    int ml;

public:
    Beer(const char* brand, int amount);
    Beer(const Beer& other);
    Beer& operator=(const Beer& other);
    ~Beer();

    const char* getName() const;
    int getMl() const;
    void add(Beer& other, int amount);
    void refill(int amount);
    bool check(const char* brand) const;

    void print() const;

private:
    void copyFrom(const Beer& other);
    void free();
};
