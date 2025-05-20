#include "creature.h"

Creature::Creature(std::string name, char symbol, int health, int damage, int gold)
    : name(name), symbol(symbol), health(health), damage(damage), gold(gold) {}

std::string Creature::getName() const
{
    return name;
}

void Creature::addDamage(int amount)
{
    damage += amount;
}

char Creature::getSymbol() const
{
    return symbol;
}

int Creature::getHealth() const
{
    return health;
}

int Creature::getDamage() const
{
    return damage;
}

int Creature::getGold() const
{
    return gold;
}

void Creature::reduceHealth(int amount)
{
    health -= amount;
}

bool Creature::isDead()
{
    return health <= 0;
}

void Creature::addGold(int amount)
{
    gold += amount;
}