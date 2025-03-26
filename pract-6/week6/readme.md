# Различни видове преобразувания (casts) в C++

## 1. static_cast

`static_cast` е най-често използваният оператор за преобразуване в C++. Той извършва преобразуване по време на компилация и се използва основно за явни преобразувания, които компилаторът счита за безопасни.

### Синтаксис:

```cpp
static_cast<нов_тип>(израз);

```

-   **израз**: Данните, които ще се преобразуват.
    
-   **нов_тип**: Желаният тип на резултата.
    

`static_cast` може да се използва за преобразуване между свързани типове, като числови типове или указатели в рамките на една и съща йерархия на наследяване.

### Пример:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 10;

    // Преобразуване на int към double
    double nd = static_cast<double>(n);

    // Извеждане на типа
    cout << typeid(n).name() << endl;
    cout << typeid(static_cast<double>(n)).name() << endl;
    cout << typeid(nd).name();

    return 0;
}

```

**Изход:**

```
i
d
d

```

### Обяснение:

Използваме `typeid()` за да проверим типа на променливите. Целочислената променлива `n` се преобразува в `double` чрез `static_cast<double>(n)`, а резултатът потвърждава успешното преобразуване.

----------

## 2. dynamic_cast

`dynamic_cast` се използва основно за понижаващо преобразуване (downcasting) в контекста на полиморфизъм и наследяване. Той осигурява безопасност чрез проверка по време на изпълнение, за да валидира преобразуването.

### Синтаксис:

```cpp
dynamic_cast<нов_тип>(израз);

```

Ако преобразуването е невъзможно:

-   За указатели връща `nullptr`.
    
-   За референции хвърля изключение `bad_cast`.
    

### Пример:

```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    virtual void speak() { cout << "Animal speaks." << endl; }
};

class Dog : public Animal {
public:
    void speak() override { cout << "Dog barks." << endl; }
};

class Cat : public Animal {
public:
    void speak() override { cout << "Cat meows." << endl; }
};

int main() {
    Animal* animalPtr = new Dog();
    Dog* dogPtr = dynamic_cast<Dog*>(animalPtr);

    if (dogPtr) {
        dogPtr->speak();
    } else {
        cout << "Failed to cast to Dog." << endl;
    }

    Cat* catPtr = dynamic_cast<Cat*>(animalPtr);
    if (catPtr) {
        catPtr->speak();
    } else {
        cout << "Failed to cast to Cat." << endl;
    }

    delete animalPtr;
    return 0;
}

```

**Изход:**

```
Dog barks.
Failed to cast to Cat.

```

### Обяснение:

`animalPtr` сочи към обект от тип `Dog`. `dynamic_cast` успешно го преобразува в `Dog*`, но неуспешно към `Cat*`, защото `animalPtr` не сочи към обект от този тип.

----------

## 3. const_cast

`const_cast` се използва за премахване на `const` или `volatile` квалификатора от променлива. Използването му трябва да става с повишено внимание, тъй като промяната на `const` обект може да доведе до неопределено поведение.

### Синтаксис:

```cpp
const_cast<нов_тип>(израз);

```

### Пример:

```cpp
#include <iostream>
using namespace std;

int main() {
    const int n = 5;
    const int* ptr = &n;
    int* nonConstPtr = const_cast<int*>(ptr);
    *nonConstPtr = 10;
    cout << *nonConstPtr;
    return 0;
}

```

**Изход:**

```
10

```

### Обяснение:

Стойността на `n` е променена чрез `const_cast`, въпреки че първоначално е била `const`. Този подход трябва да се използва с повишено внимание.

----------

## 4. reinterpret_cast

`reinterpret_cast` се използва за преобразуване на указатели към други типове указатели, без проверка за съвместимост на типовете.

### Синтаксис:

```cpp
reinterpret_cast<нов_тип>(израз);

```

### Пример:

```cpp
#include <iostream>
using namespace std;

int main() {
    int n = 10;
    int* nptr = &n;
    char* charptr = reinterpret_cast<char*>(nptr);
    cout << "Integer Address: " << nptr << endl;
    cout << "Char Address: " << charptr;
    return 0;
}

```

**Изход:**

```
Integer Address: 0x7ffcd595d6fc
Char Address: 0x7ffcd595d6fc

```

### Обяснение:

Адресът на `nptr` е интерпретиран като `char*` чрез `reinterpret_cast`. Това преобразуване може да доведе до грешки, ако не се използва внимателно.

----------

## Забележка:

Операторите `const_cast` и `reinterpret_cast` обикновено не се препоръчват, тъй като могат да доведат до грешки и неочаквано поведение.

## Задачи

*Позволено е да се добавят допълнителни полета и методи към класовете ако имате нужда от тях*

**Задача 1:** Да се създаде клас Author, в който да има следните полета:

- Собствено име - ***char****
- Последно име - ***char****
- Години - ***uint***
- Имейл - ***char****

Нека се реализират и тези функционалности:

- Getters
- Оператор <<

**Задача 2:** Да се създаде клас Book, в който да има следните полета:

- Име - ***char****
- Автори - ***Author[]***
- Цена - ***double***
- Текст - ***char****

Нека се реализират и тези функционалноти:

- Getters
- Метод, който казва дали има автор, чиито две имена съвпадат с подадените
- Метод за промяна на цената
- Метод за печатане на текстът
- Оператор <<


**Задача 3:** Да се реализира клас Library, който представлява колекция от двойки(pair) от книга и бройка.

- Книги - ***BookCountPair(Book, uint)[]***

Нека тя да има следните функционалности:

- Оператор [] - търси по име на книгата и връща бройката
- Да може да се взима книга от библиотеката
- Да може книгите да се сортират по азбучен ред
- Метод, който да връща всички книги, чиито автор е подаденият
- Метод, който казва дали дадена книга е налична