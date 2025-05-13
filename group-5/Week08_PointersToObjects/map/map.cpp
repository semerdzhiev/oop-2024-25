#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<int, const char*> m;

    m[0] = "hi";
    m[1] = "hello";

    if (m.find(0) != m.end())
    {
        cout << "Found "<< m.find(0)->second << endl;
    }
    else
    {
        cout << "Not Found" << endl;
    }
    
    return 0;
}