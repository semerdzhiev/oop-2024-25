#ifndef TIME_HPP_
#define TIME_HPP_

#include <iostream>

struct Time {
    int hours;
    int minutes;
    int seconds;

    Time();
    Time(int h, int m, int s);
    
    void addSeconds(int sec);
    void addMinutes(int min);
    void addHours(int hr);
    void normalize();
    int compare(const Time& other) const;
    void print() const;
};

#endif // TIME_HPP_