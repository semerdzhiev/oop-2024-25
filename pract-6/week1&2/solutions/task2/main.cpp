#include "Time.hpp"

using namespace std;

int main()
{
    Time times[MAX_TIMES] = {
        Time(1, 22, 33), Time(20, 15, 30), Time(23, 59, 59),
        Time(2, 30, 45), Time(21, 00, 00), Time(6, 00, 00),
        Time(0, 30, 00), Time(14, 45, 10), Time(19, 20, 00),
        Time(5, 45, 05)
    };

    cout << "Original times:" << endl;
    for (int i = 0; i < MAX_TIMES; ++i) {
        times[i].print();
    }

    customSort(times, MAX_TIMES);

    cout << "\nSorted times:" << endl;
    for (int i = 0; i < MAX_TIMES; ++i) {
        times[i].print();
    }

    return 0;
}