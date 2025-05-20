#pragma once
#include <iostream>
#include <string>

class Creature
{
private:
    std::string name;
    char symbol;
    int health;
    int damage;
    int gold;

protected:
    void addDamage(int);

public:
    Creature(std::string name, char symbol, int health, int damage, int gold);

    std::string getName() const;
    char getSymbol() const;
    int getHealth() const;
    int getDamage() const;
    int getGold() const;

    void reduceHealth(int);
    bool isDead();
    void addGold(int);
};