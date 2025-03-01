#include <iostream>
#include <fstream>
#include <iomanip>

constexpr static unsigned SECONDS_IN_MINUTE = 60;
constexpr static unsigned SECONDS_IN_HOURS = 3600;
constexpr static unsigned DAY_SECONDS = 24 * 3600;

constexpr static unsigned MAX_TIMES = 10;

class Time
{
private:
    unsigned secondsFromMidnight;

public:
    Time() : secondsFromMidnight(0) { }

    Time(unsigned hours, unsigned mins, unsigned seconds) {
        setHours(hours);
        setMins(mins);
        setSeconds(seconds);
    }

    unsigned getHours() const {
        return secondsFromMidnight / SECONDS_IN_HOURS;
    }

    unsigned getMins() const {
        return (secondsFromMidnight / SECONDS_IN_MINUTE) % 60;
    }

    unsigned getSeconds() const {
        return secondsFromMidnight % 60;
    }

    bool setHours(unsigned hours) {
        return validateAndSet(0, 23, hours, getHours(), SECONDS_IN_HOURS);
    }

    bool setMins(unsigned mins) {
        return validateAndSet(0, 59, mins, getMins(), SECONDS_IN_MINUTE);
    }

    bool setSeconds(unsigned seconds) {
        return validateAndSet(0, 59, seconds, getSeconds(), 1);
    }

    void tick() {
        ++secondsFromMidnight %= DAY_SECONDS;
    }

    // Clean visualization of time
    void serialize(std::ostream& os) const { 
        os << setw(2) << setfill('0') << getHours() << ":"
            << setw(2) << setfill('0') << getMins() << ":"
            << setw(2) << setfill('0') << getSeconds() << std::endl;
    }

    unsigned timeUntilMidnight() const {
        return DAY_SECONDS - secondsFromMidnight;
    }

    bool isDinnerTime() const {
        return (getHours() == 20 && getMins() >= 30) || (getHours() == 21) || (getHours() == 22 && getMins() == 0);
    }

    bool isPartyTime() const {
        return (getHours() >= 23 || getHours() < 6);
    }

    Time timeDifference(const Time& other) const {
        int diff = static_cast<int>(secondsFromMidnight) - static_cast<int>(other.secondsFromMidnight);
        if (diff < 0)
            diff += DAY_SECONDS;

        return Time(diff / SECONDS_IN_HOURS, (diff % SECONDS_IN_HOURS) / SECONDS_IN_MINUTE, (diff % SECONDS_IN_MINUTE));
    }

    bool isEarlierThan(const Time& other) const {
        return secondsFromMidnight < other.secondsFromMidnight;
    }

    void print() const {
        serialize(std::cout);
    }

private:
    bool validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldVlaue, unsigned multiplier) {
        if (newValue >= lowerBound && newValue <= upperBound) {
            (secondsFromMidnight -= (oldVlaue * multiplier)) += (newValue * multiplier);
            return true;
        }
        else
            return false;
    }
};

void customSort(Time times[], unsigned size) {
    bool swapped;

    for (unsigned i = 0; i < size - 1; ++i) {
        swapped = false;

        for (unsigned j = 0; j < size - 1 - i; ++j) {
            if (!times[j].isEarlierThan(times[j + 1])) {
                Time temp = times[j];
                times[j] = times[j + 1];
                times[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

bool compareTimes(const Time& t1, const Time& t2) {
    return t1.isEarlierThan(t2);
}