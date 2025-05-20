#include "monster.h"
#include <stdlib.h>
#include <time.h> 

Monster::Monster(Type type)
    : Creature(monsterData[type]) 
{
    if(type == Type::max_types)
    {
        std::cerr << "Invalid monster type!" << std::endl;
        throw std::invalid_argument("Invalid monster type");
    }
}

Monster Monster::getRandomMonster()
{
    srand (time(NULL));

    int rand_0_max_types = rand() % max_types;

    return Monster(static_cast<Type>(rand_0_max_types));
}