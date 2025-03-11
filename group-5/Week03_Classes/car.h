#pragma once

class Car {
private:
    char* brand = nullptr;
    char* engine = nullptr;
    int hp;
    int year;
    double fuelConsumption;
    double fuel;

    const char* DEFAULT_NAME = "Pernishki golf";
    const char* DEFAULT_ENGINE = "1.9 TDI";
    const int DEFAULT_HP = 100;
    const int DEFAULT_YEAR = 2000;
    const double DEFAULT_FUEL = 0;
    const double DEFAULT_FUEL_CONSUMPTION = 4.2;

    void replace(char*& dest, const char* src);

public:
    Car();
    Car(const char* brand, const char* engine, int hp, int year, double fuelConsumption);
    Car(const char* brand, const char* engine, int hp, int year, double fuelConsumption, double fuel);

    void setBrand(const char* brand);
    void setEngine(const char* engine);
    void setHp(int hp);
    void setYear(int year);
    void setFuelConsumption(double fuelConsumption);
    void setFuel(double fuel);

    const char* getBrand() const;
    const char* getEngine() const;
    int getHp() const;
    int getYear() const;
    double getFuelConsumption() const;
    double getFuel() const;

    bool drive(int km);
    void fancyDrive(const char* file, int km);
    void refuel(double fuel);

    void print() const;
    
    ~Car();
};