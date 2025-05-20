#pragma once
#include "creature.h"
#include <iostream>

class Player : public Creature
{
private:
    int level = 1;
public:
    Player(std::string name);

    int getLevel();
    void levelUp();
    bool hasWon();
};