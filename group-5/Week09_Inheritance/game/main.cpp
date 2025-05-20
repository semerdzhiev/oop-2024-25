#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h> 
#include "player.h"
#include "monster.h"

typedef bool (*Action)(Player&, Monster&);

Player initializePlayer()
{
    std::string name;
    std::cout << "Enter your name: ";

    std::cin >> name;
    Player player(name);

    std::cout << "Welcome, " << player.getName() << "!" << std::endl;

    return player;
}

enum choice
{
    run,
    fight,
    max_choices
};

void monsterAttack(Monster& monster, Player& player)
{
    player.reduceHealth(monster.getDamage());
    std::cout << "The " << monster.getName() << " attacked you for " 
         << monster.getDamage() << " damage." << std::endl;
}

void playerAttack(Player& player, Monster& monster)
{
    monster.reduceHealth(player.getDamage());
    std::cout << "You attacked the " << monster.getName() << " for " 
         << player.getDamage() << " damage." << std::endl;
}

// Returns true if the player escaped
bool Run(Player& player, Monster& monster)
{
    srand (time(NULL));

    bool is_running = (bool)(rand() % 2);
    if (is_running)
    {
        return is_running;
    }

    std::cout << "You failed to flee." << std::endl;
    monsterAttack(monster, player);
    return false;
}

bool Fight(Player& player, Monster& monster)
{
    playerAttack(player, monster);
    if (monster.isDead())
    {
        std::cout << "You have defeated the " << monster.getName() << "!" << std::endl;
        player.addGold(monster.getGold());
        player.levelUp();
        std::cout << "You have gained " << monster.getGold() << " gold." 
                  << "You are now level " << player.getLevel() << "." << std::endl;
        return true;
    }

    monsterAttack(monster, player);
    return false;
}

const std::string choiceNames[max_choices] = { "Run", "Fight" };
const char choiceLetters[max_choices] = { 'r', 'f' };
const Action actionFunctions[max_choices] = { Run, Fight };

choice getPlayerChoice()
{
    std::cout<< "(R)un or (F)ight: ";
    char input;
    
    do 
    {
        std::cin >> input;
        input = tolower(input);

        for (size_t i = 0; i < choice::max_choices; i++)
        {
            if (input == choiceLetters[i])
            {
                return static_cast<choice>(i);
            }
        }

        std::cout << "Invalid choice. Please enter 'r' or 'f': ";
    }
    while(true);
}

void playWithMonster(Player& player, Monster& monster)
{
    bool round_ended = false;

    do 
    {
        choice playerChoice = getPlayerChoice();
        Action action = actionFunctions[playerChoice];
        round_ended = action(player, monster);
    }
    while(!round_ended && !player.isDead() && !monster.isDead());
}

int main()
{
    Player player = initializePlayer();

    while (!player.isDead())
    {
        Monster monster = Monster::getRandomMonster();
        std::cout << "You have encountered a "
                  << monster.getName()
                  << " (" << monster.getSymbol() << ")." 
                  << std::endl;
        
        playWithMonster(player, monster);

        if (player.isDead())
        {
            std::cout << "You have died with "
                << player.getGold() << " gold, "
                << player.getLevel() << " level " << std::endl;
            break;
        }
        else if (player.getLevel() == 20)
        {
            std::cout << "You have won the game!" << std::endl;
            break;
        }
    }
}