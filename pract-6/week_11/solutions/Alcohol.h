#ifndef ALCOHOL_H
#define ALCOHOL_H

#include "Drink.h"

class Alcohol : public Drink {
public:
	Alcohol(std::string name, const int quantity, std::string description, const double price, const ServingType servingType, const double alcoholPercentage);

	const double getAlcoholPercentage() const;

	std::string getInfo() const override;

	MenuItem* clone() const override;

private:
	double m_alcoholPercentage;
};

#endif // !ALCOHOL_H
