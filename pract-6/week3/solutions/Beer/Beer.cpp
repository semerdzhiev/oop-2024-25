#include "Beer.hpp"

Beer::Beer(const char* brand, int amount) : ml(amount) {
	name = new(std::nothrow) char[strlen(brand) + 1];
	if (name) {
		strcpy(name, brand);
	} else {
		std::cerr << "Memory allocation failed for name!" << std::endl;
		ml = 0;
	}
}

Beer::Beer(const Beer& other) {
	copyFrom(other);
}

Beer& Beer::operator=(const Beer& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Beer::~Beer() {
	free();
}

const char* Beer::getName() const {
	return name;
}

int Beer::getMl() const {
	return ml;
}

void Beer::add(Beer& other, int amount) {
	if (amount > other.ml) {
		amount = other.ml;
	}

	char* newName = new(std::nothrow) char[strlen(name) + strlen(other.name) + 2]; // 2 because of the '&' and '\0'
	if (newName) {
		strcpy(newName, name);
		strcat(newName, "&");
		strcat(newName, other.name);
		free();
		name = newName;
	} else {
		std::cerr << "Memory allocation failed for name concatenation!" << std::endl;
		return;
	}

	ml += amount;
	other.ml -= amount;
}

void Beer::refill(int amount) {
	ml += amount;
}

bool Beer::check(const char* brand) const {
	return strstr(name, brand) != nullptr;
}

void Beer::print() const {
	std::cout << name << ", " << ml << "ml" << std::endl;
}

void Beer::copyFrom(const Beer& other) {
	name = new(std::nothrow) char[strlen(other.name) + 1];
	if (name) {
		strcpy(name, other.name);
		ml = other.ml;
	} else {
		std::cerr << "Memory allocation failed for copy constructor!" << std::endl;
		ml = 0;
	}
}

void Beer::free() {
	delete[] name;
}
