#include "player.h"

Player::Player(std::string name) 
    : Creature(name, '@', 10, 1, 0) {}

int Player::getLevel()
{
    return level;
}

void Player::levelUp()
{
    ++level;
    addDamage(1);
}

bool Player::hasWon()
{
    return level == 20;
}
