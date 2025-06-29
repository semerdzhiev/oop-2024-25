#ifndef DRINK_H
#define DRINK_H

#include "MenuItem.h"
#include "ServingType.h"

class Drink : public MenuItem {
public:
	Drink(std::string name, const int quantity, std::string description, const double price, const ServingType servingType);

	std::string getInfo() const override;

	MenuItem* clone() const override;

protected:
	ServingType m_servingType;
};

#endif // !DRINK_H
