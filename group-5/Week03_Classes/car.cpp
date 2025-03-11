#include "car.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

Car::Car()
{
    Car(DEFAULT_NAME, DEFAULT_ENGINE, DEFAULT_HP, DEFAULT_YEAR, DEFAULT_FUEL);
}

Car::Car(const char* brand, const char* engine, int hp, int year, double fuelConsumption)
{
    Car(brand, engine, hp, year, DEFAULT_FUEL_CONSUMPTION);
}

Car::Car(const char* brand, const char* engine, int hp, int year, double fuelConsumption, double fuel)
{
    setBrand(brand);
    setEngine(engine);
    setHp(hp);
    setYear(year);
    setFuelConsumption(fuelConsumption);
    setFuel(fuel);
}

void Car::replace(char*& dest, const char* src)
{
    if (dest != nullptr)
    {
        delete[] dest;
    }

    dest = new char[strlen(src) + 1];
    strcpy(dest, src);
}

void Car::setBrand(const char* brand1)
{
    replace(brand, brand1);
}

void Car::setEngine(const char* engine1)
{
    replace(engine, engine1);
}

void Car::setHp(int hp)
{
    this->hp = hp;
}

void Car::setYear(int year)
{
    this->year = year;
}

void Car::setFuelConsumption(double fuelConsumption)
{
    this->fuelConsumption = fuelConsumption;
}

void Car::setFuel(double fuel)
{
    this->fuel = fuel;
}

const char* Car::getBrand() const
{
    return brand;
}

const char* Car::getEngine() const
{
    return engine;
}

int Car::getHp() const
{
    return hp;
}

int Car::getYear() const
{
    return year;
}

double Car::getFuelConsumption() const
{
    return fuelConsumption;
}   

double Car::getFuel() const
{
    return fuel;
}

/*
fuelConsumtion = 4.5 / 100 = 0.045
fuelUsed = km * 0.045
*/

// TODO: fancy drive from file
bool Car::drive(int km)
{
    double fuelUsed = (double)km * (fuelConsumption / 100.0);

    if (fuelUsed > fuel)
    {
        return false;
    }

    fuel -= fuelUsed;
    return true;
}

Car::~Car()
{
    delete[] brand;
    delete[] engine;
}

void Car::refuel(double fuel)
{

    this->fuel += fuel;
}

void Car::print() const
{
    cout << "Brand: " << brand << endl;
    cout << "Engine: " << engine << endl;
    cout << "HP: " << hp << endl;
    cout << "Year: " << year << endl;
    cout << "Fuel consumption: " << fuelConsumption << endl;
    cout << "Fuel: " << fuel << endl;
}

void Car::fancyDrive(const char* file, int km)
{
    if (!drive(km))
    {
        return;
    }

    fstream f(file, ios::out | ios::ate | ios::app);

    if (!f.is_open())
    {
        cout << "File not opened!" << endl;
        return;
    }
    
    
    for (int i = 0; i < km - 1; i++)
    {
        f << ".";
    }
    f << "|";
}