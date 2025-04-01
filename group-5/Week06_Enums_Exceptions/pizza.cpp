#include <iostream>
#include "pizza.hpp"

using namespace std;

const char* toString(PizzaSize size)
{
    switch (size)
    {
    case PizzaSize::Small:
        return "small";
    case PizzaSize::Medium:
        return "medium";
    case PizzaSize::Large:
        return "large";
    }
}

const char* toString(PizzaSauce sauce)
{
    switch (sauce)
    {
    case PizzaSauce::Tomato:
        return "tomato";
    case PizzaSauce::Cream:
        return "cream";
    case PizzaSauce::Truffel:
        return "truffel";
    }
}

const char* toString(PizzaTopping topping)
{
    switch (topping)
    {
    case PizzaTopping::Olives:
        return "olives";
    case PizzaTopping::Peppers:
        return "peppers";
    case PizzaTopping::Mushrooms:
        return "mushrooms";
    case PizzaTopping::Onion:
        return "onion";
    }
}

const char* toString(MeatTopping topping)
{
    switch (topping)
    {
    case MeatTopping::Pepperoni:
        return "pepperoni";
    case MeatTopping::Chicken:
        return "chicken";
    case MeatTopping::Anchovia:
        return "anchovia";
    case MeatTopping::Chorizo:
        return "chorizo";
    }
}

const char* toString(CheeseTopping topping)
{
    switch (topping)
    {
    case CheeseTopping::Mozzarella:
        return "mozzarella";
    case CheeseTopping::Cheddar:
        return "cheddar";
    case CheeseTopping::Feta:
        return "feta";
    default:
        return "unknown";
    }
}

void Pizza::setSize(PizzaSize size)
{
    this->size = size;
}

void Pizza::setSauce(PizzaSauce sauce)
{
    this->sauce = sauce;
}

void Pizza::addTopping(PizzaTopping topping)
{
    toppings.push_back(topping);
}

void Pizza::addMeatTopping(MeatTopping topping)
{
    meatToppings.push_back(topping);
}

void Pizza::addCheeseTopping(CheeseTopping topping)
{
    cheeseToppings.push_back(topping);
}

void Pizza::print() const
{
    cout << "Pizza size: " << toString(size) << endl;
    cout << "Pizza sauce: " << toString(sauce) << endl;

    cout << "Pizza toppings: " << endl;
    for (size_t i = 0; i < toppings.size(); i++)
    {
        cout << "\t - " << toString(toppings[i]) << endl;
    }
    
    if (!meatToppings.empty())
    {
        cout << "Pizza meat toppings: " << endl;
    }
    for (size_t i = 0; i < meatToppings.size(); i++)
    {
        cout << "\t - " << toString(meatToppings[i]) << endl;
    }

    cout << "Pizza cheese toppings: " << endl;
    for (size_t i = 0; i < cheeseToppings.size(); i++)
    {
        cout << "\t - " << toString(cheeseToppings[i]) << endl;
    }
}

PizzaSize Pizza::getSize()
{ 
    return size;
}

PizzaSauce Pizza::getSauce()
{
    return sauce;
}

const std::vector<PizzaTopping>& Pizza::getToppings()
{
    return toppings;
}

const std::vector<MeatTopping>& Pizza::getMeatToppings()
{
    return meatToppings;
}

const std::vector<CheeseTopping>& Pizza::getCheeseToppings()
{
    return cheeseToppings;
}