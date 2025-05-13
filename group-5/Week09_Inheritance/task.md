# Task

## Overview

In this task, we will create a simple game where the player fights monsters. The objective is to collect as much gold as possible before either dying or reaching level 20. The program will consist of three classes: `Creature`, `Player`, and `Monster`. Both `Player` and `Monster` inherit from `Creature`.

---

## Step-by-Step Instructions

### 1. **Create the `Creature` Class**

The `Creature` class will have the following attributes:
- `std::string name`: The name of the creature.
- `char symbol`: A single character representing the creature.
- `int health`: The creature's health points.
- `int damage`: The damage the creature deals per attack.
- `int gold`: The amount of gold the creature carries.

#### Member Functions:
- **Getters**: Provide a getter function for each attribute.
- `void reduceHealth(int)`: Reduces the creature's health by the given amount.
- `bool isDead()`: Returns `true` if the creature's health is 0 or less.
- `void addGold(int)`: Adds the specified amount of gold to the creature.

#### Example Program:
```cpp
#include <iostream>
#include <string>

int main()
{
    Creature o{ "orc", 'o', 4, 2, 10 };
    o.addGold(5);
    o.reduceHealth(1);
    std::cout << "The " << o.getName() << " has " << o.getHealth() << " health and is carrying " << o.getGold() << " gold.\n";

    return 0;
}
```

**Expected Output:**
```
The orc has 3 health and is carrying 15 gold.
```

---

### 2. **Create the `Player` Class**

The `Player` class inherits from `Creature` and has one additional attribute:
- `int level`: The player's level, starting at 1.

#### Initialization:
- The player's name is entered by the user.
- The player uses the symbol `@`, starts with 10 health, deals 1 damage, and has no gold.

#### Member Functions:
- `void levelUp()`: Increases the player's level and damage by 1.
- `int getLevel()`: Returns the player's current level.
- `bool hasWon()`: Returns `true` if the player reaches level 20.

#### Example Program:
```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;

    Player p{ name };
    std::cout << "Welcome, " << p.getName() << ".\n";
    std::cout << "You have " << p.getHealth() << " health and are carrying " << p.getGold() << " gold.\n";

    return 0;
}
```

**Expected Output:**
```
Enter your name: Alex
Welcome, Alex.
You have 10 health and are carrying 0 gold.
```

---

### 3. **Create the `Monster` Class**

The `Monster` class inherits from `Creature` and introduces an `enum` named `Type` to represent different monster types:
- `dragon`, `orc`, `slime`, and `max_types` (used for array bounds).

#### Monster Attributes:
| Type    | Name    | Symbol | Health | Damage | Gold |
|---------|---------|--------|--------|--------|------|
| dragon  | dragon  | D      | 20     | 4      | 100  |
| orc     | orc     | o      | 4      | 2      | 25   |
| slime   | slime   | s      | 1      | 1      | 10   |

#### Constructor:
The `Monster` constructor takes a `Type` enum and initializes the monster using a lookup table (`static inline Creature monsterData[]`).

#### Example Program:
```cpp
#include <iostream>
#include <string>

int main()
{
    Monster m{ Monster::Type::orc };
    std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";

    return 0;
}
```

**Expected Output:**
```
A orc (o) was created.
```

---

### 4. **Add Random Monster Generation**

Add a static function `Monster::getRandomMonster()` that:
- Picks a random number between `0` and `max_types - 1`.
- Returns a monster of the corresponding type.

#### Example Program:
```cpp
#include <iostream>
#include <string>

int main()
{
    for (int i{ 0 }; i < 10; ++i)
    {
        Monster m{ Monster::getRandomMonster() };
        std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
    }

    return 0;
}
```

**Expected Output:**
The output will vary as the monsters are generated randomly.

---

### 5. **Game Logic**

Here are the rules for the game:

- The player encounters one randomly generated monster at a time.
- For each monster, the player has two choices: (R)un or (F)ight.
  - If the player decides to Run, they have a 50% chance of escaping.
    - If the player escapes, they move to the next encounter with no ill effects.
    - If the player does not escape, the monster gets a free attack, and the player chooses their next action.
  - If the player chooses to fight, the player attacks first. The monster’s health is reduced by the player’s damage.
    - If the monster dies, the player takes any gold the monster is carrying. The player also levels up, increasing their level and damage by 1.
    - If the monster does not die, the monster attacks the player back. The player’s health is reduced by the monster’s damage.
- The game ends when the player has died (loss) or reached level 20 (win).
  - If the player dies, the game should tell the player what level they were and how much gold they had.
  - If the player wins, the game should tell the player they won, and how much gold they had.

#### Example Game Session:

```
Enter your name: Alex
Welcome, Alex
You have encountered a slime (s).
(R)un or (F)ight: f
You hit the slime for 1 damage.
You killed the slime.
You are now level 2.
You found 10 gold.
You have encountered a dragon (D).
(R)un or (F)ight: r
You failed to flee.
The dragon hit you for 4 damage.
(R)un or (F)ight: r
You successfully fled.
You have encountered a orc (o).
(R)un or (F)ight: f
You hit the orc for 2 damage.
The orc hit you for 2 damage.
(R)un or (F)ight: f
You hit the orc for 2 damage.
You killed the orc.
You are now level 3.
You found 25 gold.
You have encountered a dragon (D).
(R)un or (F)ight: r
You failed to flee.
The dragon hit you for 4 damage.
You died at level 3 and with 35 gold.
Too bad you can’t take it with you!
```

#### Hint: Create 4 Functions

- The `main()` function should handle game setup (creating the Player) and the main game loop.
- `fightMonster()` handles the fight between the Player and a single Monster, including asking the player what they want to do, handling the run or fight cases.
- `attackMonster()` handles the player attacking the monster, including leveling up.
- `attackPlayer()` handles the monster attacking the player.