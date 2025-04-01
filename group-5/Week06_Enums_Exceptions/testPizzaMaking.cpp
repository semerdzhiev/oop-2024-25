#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "pizzaMaker.hpp"
#include "pizza.hpp"
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

TEST_CASE("Bake throws error when topping is missing")
{
    PizzaMaker maker;

    maker.addCheeseTopping(CheeseTopping::Cheddar)
        .setSize(PizzaSize::Large)
        .setSauce(PizzaSauce::Cream)
        .addCheeseTopping(CheeseTopping::Feta);

    REQUIRE_THROWS_WITH(maker.bake(), "Pizza doesn't have toppings YET!");
}

TEST_CASE("Pizza maker correctly constructs pizza")
{
    PizzaMaker maker;

    maker.setSize(PizzaSize::Large)
        .setSauce(PizzaSauce::Cream)
        .addCheeseTopping(CheeseTopping::Feta)
        .addTopping(PizzaTopping::Onion);

    Pizza pizza = maker.bake();

    REQUIRE(pizza.getSize() == PizzaSize::Large);
    REQUIRE(pizza.getSauce() == PizzaSauce::Cream);
    REQUIRE(pizza.getCheeseToppings().size() == 1);
    REQUIRE(pizza.getCheeseToppings()[0] == CheeseTopping::Feta);
    REQUIRE(pizza.getToppings().size() == 1);
    REQUIRE(pizza.getToppings()[0] == PizzaTopping::Onion);
    REQUIRE(pizza.getMeatToppings().empty());
}