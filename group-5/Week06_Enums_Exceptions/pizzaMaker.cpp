#include "pizzaMaker.hpp"

PizzaMaker& PizzaMaker::setSize(PizzaSize size)
{
    pizza.setSize(size);
    return *this;
}

PizzaMaker& PizzaMaker::setSauce(PizzaSauce sauce)
{
    pizza.setSauce(sauce);
    return *this;
}

PizzaMaker& PizzaMaker::addTopping(PizzaTopping topping)
{
    pizza.addTopping(topping);
    return *this;
}

PizzaMaker& PizzaMaker::addMeatTopping(MeatTopping topping)
{
    pizza.addMeatTopping(topping);
    return *this;
}

PizzaMaker& PizzaMaker::addCheeseTopping(CheeseTopping topping)
{
    pizza.addCheeseTopping(topping);
    return *this;
}

void PizzaMaker::reset()
{
    pizza = Pizza();
}

Pizza PizzaMaker::bake()
{
    if (pizza.toppings.empty())
    {
        throw "Pizza doesn't have toppings YET!";
    }

    if (pizza.cheeseToppings.empty())
    {
        throw "Pizza doesn't have cheese toppings YET!";
    }

    Pizza bakedPizza = pizza;
    reset();
    return bakedPizza;
}