# Приятелски функции и класове

Приятелските функции и класове имат пряк достъп до всички членове (дори ако са декларирани като `public`, `private` или `protected`) на приятелския си клас. Те се декларират, като поставим запазената дума `friend` пред прототипа на функцията или класа.

Пример:
```cpp
class Point2D {
	...
	friend double pointsDist(const Point2D&, const Point2D&);
	...
};

// Външна функция, която има пряк достъп до член-данните на класа Point2D
double pointsDist(const Point2D& p1, const Point2D& p2) {
	return sqrt(
		pow(p2.x - p1.x, 2) +
		pow(p2.y - p1.y, 2)
	);
}
```

```cpp
class A {
	...
	friend class B; // Всички методи на класа B имат пряк достъп
					// до всички компоненти на класа A
	...
};
```

---
# Предефиниране на оператори

***Важно***: Предефинирането на оператори запазва оригиналния приоритет, асоциативност, броят и позицията на аргументите му. Връщаният тип е произволен.

Името на операторната функция започва със запазената дума `operator`, последвана от символа (или името) на оператора, който ще бъде променен.
*Пример:*
```cpp
void operator delete(void*)
bool operator<(const MyObject& other);
```

Можем да предефинираме следните оператори: 
```
+, -, *, /, %, ^, &, |, ~, !, =, , +=, -=, *=, /=, %=, ^=, &=,
|=, <>, >>=, <<=, ==, !=, <=, >=, &&, ||, ++, --, ->*, ->,
[], new, delete
```

Примери:
```cpp
// предефиниране на префиксен ++
Rational& Rat::operator++() {
	numer = numer + denom;
	return *this;
}

// предефиниране на постфиксен ++
Rational Rat::operator++(int) { // тук връщаме копие!!!
	Rat temp = *this;
	numer = numer + denom;
	return temp;
}
```


При предефинирането като член-функция, първият (или единственият) операнд не се подава като параметър – неговата роля се изпълнява от обекта, към който сочи указателят `this`.

Когато първият (или единственият) операнд на оператор, който искаме да предефинираме е обект на друг клас или псевдоним на обект на друг клас, или е от стандартен в езика тип (int, double, char и т.н.), операторът трябва да се реализира като приятелска функция на класа.

Защо е нужно да предефинираме някои оператори като приятелски функции?
*Пример:*
```cpp
#include <iostream>

class Point {
private:
    int x, y;
public:
    Point(int a = 0, int b = 0) : x(a), y(b) {}

    // Опит за дефиниция като член-функция 
    std::ostream& operator<<(std::ostream& os) const {
        os << "(" << x << ", " << y << ")";
        return os;
    }
};

int main() {
    Point p(3, 4);
    std::cout << p; // Какво ще се случи тук? -> Грешка!
    return 0;
}
```

*Причина:*
Това би довело до грешка. Ще се интерпретира като `p.operator<<(cout)` (тъй като винаги имаме this като първи аргумент по подразбиране) което ще доведе до
`p << cout`, което е грешка. За да се справим с този проблем, изполваме приятелски функции.

*Правилен пример с приятелска функция:*
```cpp
class Point {
	...
	friend std::ostream& operator<<(std::ostream& os, const Point& p);
		...
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
```

---
# Задача

Създайте клас `Vector`, който управлява динамичен масив от цели числа. Този клас трябва да се грижи за собственото си управление на паметта чрез имплементация на конструктор за копиране, оператор за присвояване (`operator=`) и деструктор. Вашият клас `Vector` трябва да поддържа следните функционалности:

- **`push_back(int value)`**: Добавя стойност в края на вектора.
- **`pop_back()`**: Премахва последния елемент от вектора.
- **`at(int index)`**: Връща стойността на посочения индекс.
- **`insert_at(int index, int value)`**: Вмъква стойност на посочения индекс.
- **`delete_at(int index)`**: Изтрива елемента на посочения индекс.
- **`sort()`**: Сортира вектора в нарастващ ред.
- **`concat(const Vector& other)`**: Конкатенира друг обект `Vector` в края на този вектор.
- **`slice(int start, int end)`**: Връща нов `Vector`, който е подмножество от `start` до `end` индекси.
- **`reverse()`**: Пренарежда елементите в обратен ред

Предефинирайте и следните оператори:
- `operator[]` - За достъп до елемент по индекс.
- `operator+` - За конкатенация на два вектора.
- `operator==` - За сравнение на два вектора.
- `operator<<` - За отпечатване на съдържанието на вектора на конзолата.
- `operator*` - За изчисляване на скаларното произведение на два вектора. Ако векторите имат различна дължина, итерацията спира след достигане на края на по-малкия от тях.