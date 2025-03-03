#include "Time.hpp"

Time::Time() : hours(0), minutes(0), seconds(0) {}
Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

void Time::addSeconds(int sec) {
    seconds += sec;
    normalize();
}

void Time::addMinutes(int min) {
    minutes += min;
    normalize();
}

void Time::addHours(int hr) {
    hours += hr;
    normalize();
}

void Time::normalize() {
    if (seconds >= 60) {
        minutes += seconds / 60;
        seconds %= 60;
    } else if (seconds < 0) {
        int borrow = (-seconds + 59) / 60;
        minutes -= borrow;
        seconds += borrow * 60;
    }
    if (minutes >= 60) {
        hours += minutes / 60;
        minutes %= 60;
    } else if (minutes < 0) {
        int borrow = (-minutes + 59) / 60;
        hours -= borrow;
        minutes += borrow * 60;
    }
}

int Time::compare(const Time& other) const {
    int total1 = hours * 3600 + minutes * 60 + seconds;
    int total2 = other.hours * 3600 + other.minutes * 60 + other.seconds;
    
    if (total1 == total2)
        return 0;
    else if (total1 < total2)
        return -1;
    else
        return 1;
}

void Time::print() const {
    if (hours < 10) std::cout << "0";
    std::cout << hours << ":";
    if (minutes < 10) std::cout << "0";
    std::cout << minutes << ":";
    if (seconds < 10) std::cout << "0";
    std::cout << seconds << std::endl;
}