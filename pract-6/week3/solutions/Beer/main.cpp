#include <iostream>
#include <cstring>

#include "Beer.hpp"

using namespace std;

int main() {
	Beer beer1("Corona", 500);
	Beer beer2("Heineken", 500);

	beer1.print(); // Corona, 500ml
	beer2.print(); // Heineken, 500ml

	beer1.add(beer2, 250);

	beer1.print(); // Corona & Heineken, 750ml
	beer2.print(); // Heineken, 250ml

	cout << beer1.check("Heineken") << std::endl; // true
	cout << beer1.check("Stella Artois") << std::endl;// false
	cout << beer1.check(beer2.getName()) << std::endl;// true
}

