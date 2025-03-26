#pragma once

struct Position {
    double x = 0;
    double y = 0;

    Position() = default;

    Position(double _x, double _y) : x(_x), y(_y) {};

    void print() const { std::cout << '(' << x << ',' << y << ')'; }
};