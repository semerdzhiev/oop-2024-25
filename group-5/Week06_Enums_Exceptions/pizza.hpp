#pragma once
#include <vector>
#include <iostream>

enum class PizzaSize { Small, Medium, Large };
enum class PizzaSauce { Tomato, Cream, Truffel };
enum class PizzaTopping { Olives, Peppers, Mushrooms, Onion };
enum class MeatTopping { Pepperoni, Chicken, Anchovia, Chorizo };
enum class CheeseTopping { Mozzarella, Cheddar, Feta };

class PizzaMaker;

class Pizza
{
private:
    PizzaSize size;
    PizzaSauce sauce;
    std::vector<PizzaTopping> toppings;
    std::vector<MeatTopping> meatToppings;
    std::vector<CheeseTopping> cheeseToppings;
    
    Pizza() = default;
    
    void setSize(PizzaSize size);
    void setSauce(PizzaSauce sauce);
    void addTopping(PizzaTopping topping);
    void addMeatTopping(MeatTopping topping);
    void addCheeseTopping(CheeseTopping topping);

    friend class PizzaMaker;
public:
    PizzaSize getSize();
    PizzaSauce getSauce();
    const std::vector<PizzaTopping>& getToppings();
    const std::vector<MeatTopping>& getMeatToppings();
    const std::vector<CheeseTopping>& getCheeseToppings();

    void print() const;
};
