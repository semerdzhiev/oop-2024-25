#include<iostream>
#include "pizzaMaker.hpp"

using namespace std;

int main()
{
    PizzaMaker maker;

    maker.addCheeseTopping(CheeseTopping::Cheddar);
        // .addTopping(PizzaTopping::Olives);

    maker.setSize(PizzaSize::Large)
        .setSauce(PizzaSauce::Cream)
        .addCheeseTopping(CheeseTopping::Feta);

    try 
    {
        Pizza pizza = maker.bake();
        pizza.print();
    }
    catch(const char* error)
    {
        cout << error << endl;
    }
}