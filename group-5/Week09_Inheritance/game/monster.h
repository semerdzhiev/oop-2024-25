#pragma once
#include "creature.h"
#include <iostream>

class Monster : public Creature
{
private:
    /*
    dragon	D	20	4	100
orc	orc	o	4	2	25
slime	slime	s	1	1	10
    */
    static inline Creature monsterData[] =
    {
        Creature("dragon", 'D', 20, 4, 100),
        Creature("orc", 'o', 4, 2, 25),
        Creature("slime", 's', 1, 1, 10),
        Creature("temp", 't', 0, 0, 0) // Placeholder for max_types
    };
public:
    enum Type
    {
        dragon,
        orc, 
        slime,
        max_types
    };

    Monster(Type type);

    static Monster getRandomMonster();
};