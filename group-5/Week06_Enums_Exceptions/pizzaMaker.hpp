#pragma once
#include "pizza.hpp"

class PizzaMaker
{
private:
    Pizza pizza;

public:
    PizzaMaker& setSize(PizzaSize size);
    PizzaMaker& setSauce(PizzaSauce sauce);
    PizzaMaker& addTopping(PizzaTopping topping);
    PizzaMaker& addMeatTopping(MeatTopping topping);
    PizzaMaker& addCheeseTopping(CheeseTopping topping);
    void reset();

    Pizza bake();
};