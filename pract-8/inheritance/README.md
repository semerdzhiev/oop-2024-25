# Наследяване в C++

Наследяването е ключова концепция в обектно-ориентираното програмиране (ООП), която позволява на един клас да "наследява" свойства и поведение от друг клас. Това улеснява повторното използване на код, организирането на класове в йерархии и създаването на по-абстрактни и гъвкави програми. Наследяването позволява на нов клас (наречен **подклас** или **производен клас**) да наследи член-променливи и член-функции от съществуващ клас (наречен **базов клас** или **родителски клас**). Производният клас може да добавя нови членове или да променя поведението на наследените членове.

---

## Единично наследяване

Единичното наследяване е най-простият вид наследяване, при което един клас наследява от точно един базов клас.

### Пример за единично наследяване

```cpp
#include <iostream>

class Animal {
private:
	int age;
public:
	Animal(int age) {
		this->age = age;
	}
    void eat() const {
        std::cout << "Animal is eating." << std::endl;
    }
};

class Dog : public Animal {
private:
	std::string breed;
public:
	Dog(int age, const std::string& breed) : Animal(age), breed(breed) {}
    void bark() const {
        std::cout << "Dog is barking." << std::endl;
    }
};

int main() {
    Dog dog(3, "Labrador");
    dog.eat();  // Извиква наследения метод от Animal
    dog.bark(); // Извиква собствения метод на Dog
    return 0;
}
```

В този пример:
- `Animal` е базовият клас с метод `eat()`.
- `Dog` е производният клас, който наследява `eat()` и добавя нов метод `bark()`.

## Множествено наследяване

Множественото наследяване позволява на един клас да наследява от повече от един базов клас. Това може да бъде полезно, но също така може да доведе до сложности, като **диамантения проблем** (обяснен по-късно).

### Пример за множествено наследяване

```cpp
#include <iostream>

class Flyer {
public:
    void fly() const {
        std::cout << "Flying." << std::endl;
    }
};

class Swimmer {
public:
    void swim() const {
        std::cout << "Swimming." << std::endl;
    }
};

class Duck : public Flyer, public Swimmer {
public:
    void quack() const {
        std::cout << "Quack!" << std::endl;
    }
};

int main() {
    Duck duck;
    duck.fly();   // Наследено от Flyer
    duck.swim();  // Наследено от Swimmer
    duck.quack(); // Собствен метод на Duck
    return 0;
}
```

В този пример:
- `Duck` наследява от `Flyer` и `Swimmer`, като получава методите `fly()` и `swim()`.

---

## Достъп до наследени компоненти

Когато един клас наследява от друг, той може да достъпва член-променливите и член-функциите на базовия клас в зависимост от техните модификатори за достъп (`public`, `protected`, `private`).

- **`public`** членове на базовия клас са достъпни от производния клас и от външни обекти.
- **`protected`** членове на базовия клас са достъпни само от производния клас, но не и от външни обекти.
- **`private`** членове на базовия клас са недостъпни за производния клас.

### Пример за достъп до наследени компоненти

```cpp
class Base {
public:
    int publicVar;
protected:
    int protectedVar;
private:
    int privateVar;
};

class Derived : public Base {
public:
    void accessMembers() {
        publicVar = 1;    // Достъпно
        protectedVar = 2; // Достъпно
        // privateVar = 3; // Недостъпно, грешка при компилация
    }
};
```

---

## Видимост при наследяване

Видимостта на наследените членове зависи от начина, по който се извършва наследяването. В C++ има три типа наследяване:

- **`public`** наследяване: Запазва видимостта на базовите членове.
- **`protected`** наследяване: Прави всички наследени `public` членове да бъдат `protected` в производния клас.
- **`private`** наследяване: Прави всички наследени членове да бъдат `private` в производния клас.

### Пример за различни типове наследяване

```cpp
class Base {
public:
    void publicMethod() {}
protected:
    void protectedMethod() {}
};

class DerivedPublic : public Base {
    // publicMethod() е public
    // protectedMethod() е protected
};

class DerivedProtected : protected Base {
    // publicMethod() е protected
    // protectedMethod() е protected
};

class DerivedPrivate : private Base {
    // publicMethod() е private
    // protectedMethod() е private
};
```

---

## Диамантен проблем

Диамантеният проблем възниква при множествено наследяване, когато два базови класа имат общ предшественик. Това може да доведе до двусмислие, тъй като производният клас може да наследи едни и същи членове по няколко пътя.

### Пример за диамантен проблем

```cpp
class Animal {
public:
    void eat() { std::cout << "Animal eats." << std::endl; }
};

class Mammal : public Animal {};
class Bird : public Animal {};

class Bat : public Mammal, public Bird {};

int main() {
    Bat bat;
    // bat.eat(); // Грешка: двусмислие - от кой базов клас да се извика eat()?
    return 0;
}
```

За да се реши този проблем, C++ използва **виртуално наследяване**, което гарантира, че само една копия на общия базов клас се наследява.

### Решение с виртуално наследяване

```cpp
class Animal {
public:
    void eat() { std::cout << "Animal eats." << std::endl; }
};

class Mammal : public virtual Animal {};
class Bird : public virtual Animal {};

class Bat : public Mammal, public Bird {};

int main() {
    Bat bat;
    bat.eat(); // Сега работи, извиква се от общия базов клас Animal
    return 0;
}
```

---

## Upcast и Downcast

### Upcast

**Upcast** е процесът на преобразуване на указател или референция от производен клас към базов клас. Това е безопасно и се извършва автоматично.

```cpp
Dog dog;
Animal* animalPtr = &dog; // Upcast: Dog* към Animal*
```

### Downcast

**Downcast** е процесът на преобразуване на указател или референция от базов клас към производен клас. Това не е безопасно и изисква изрично преобразуване, обикновено с `dynamic_cast` (за полиморфни класове).

```cpp
Animal* animalPtr = new Dog();
Dog* dogPtr = dynamic_cast<Dog*>(animalPtr); // Downcast
if (dogPtr) {
    dogPtr->bark();
}
```

Ако `dynamic_cast` не успее, връща `nullptr` за указатели или хвърля `std::bad_cast` за референции.

