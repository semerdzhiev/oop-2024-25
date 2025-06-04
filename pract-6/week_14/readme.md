
# Преобразуване между типове, Factory Pattern, Множествено наследяване и Шаблони в C++

## Множествено наследяване

Множественото наследяване позволява на "детски" клас да наследява от повече от един родителски клас.

![Multiple Inheritance](https://d33wubrfki0l68.cloudfront.net/67512abb598d0aef77410deee207b42323b17f8e/70284/wp-content/uploads/2018/07/multiple-inheritance.png)

### Конструктори и оператор за присвояване

При използване на множествено наследяване, когато копираме обект, трябва да се уверим, че всички базови класове са коректно копирани:

```cpp
MyClass(const MyClass& other) : SuperClass1(other), SuperClass2(other), SuperClass3(other), SuperClass4(other)
{
    copyFrom(other); // копираме само нещата от MyClass
}

MyClass& operator=(const MyClass& other)
{
    if (this != &other)
    {
        SuperClass1::operator=(other);
        SuperClass2::operator=(other);
        SuperClass3::operator=(other);
        SuperClass4::operator=(other);
        free();
        copyFrom(other);
    }
    return *this;
}

```

## Диамантен проблем

![](https://i.stack.imgur.com/MqMW0.png)

### Проблем

Класът `D` наследява едновременно `B` и `C`, които от своя страна наследяват `A`. В резултат — `D` има две копия на `A`.

### Решение

Използваме **виртуално наследяване** за споделяне на базовия клас:

```cpp
class A { ... };
class B : virtual public A { ... };
class C : virtual public A { ... };
class D : public B, public C {
public:
    D(...) : A(...), B(...), C(...) {}
};
```

-   `A` се създава веднъж, независимо от колко наследници има
    
-   Конструкторът на `D` трябва **явно** да инициализира `A`
    

----------

## Templates в C++

Шаблоните ни помагат да пишем обобщени класове и функции, като предотвратяват дублиране на код и излишно претоварване.

> **Важно:** C++ шаблоните са различни от generics в Java/C#!

### Шаблони на функции (Function Templates)

```cpp
template <typename T>
void printArray(T* arr, int length) {
    for (int i = 0; i < length; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
```

-   `T` се определя при извикване на функцията
    

### Шаблони на класове (Class Templates)

```cpp
template <typename T>
class Box {
private:
    T data;
public:
    Box(const T& value) : data(value) {}
    T get() const { return data; }
};
```

#### Стойности по подразбиране

```cpp
template <typename T = int, typename S = double>
class Pair {
public:
    T first;
    S second;
};
```

#### Alias Templates

```cpp
template <typename T>
class Box { };

using IntegerBox = Box<int>;

```

### Специализация на шаблони

#### Пълна специализация

```cpp
template <typename T>
class Printer {
public:
    static void print(const T& x) {
        std::cout << x << std::endl;
    }
};

template <>
class Printer<char*> {
public:
    static void print(char* const& x) {
        std::cout << "C-string: " << x << std::endl;
    }
};

```

#### Частична специализация

```cpp
template <typename K, typename V>
class Map { };

template <typename K>
class Map<K, bool> { };

```

#### Специализация на член-функции

```cpp
template <typename T>
class Calculator {
public:
    T add(T a, T b) { return a + b; }
    void print(const T& x) { std::cout << x << std::endl; }
};

template <>
void Calculator<int>::print(const int& x) {
    std::cout << "int value: " << x << std::endl;
}

```

----------

## Variadic Templates

Позволяват шаблони с произволен брой параметри:

```cpp
void printAll() {
    std::cout << std::endl;
}

template <typename T, typename... Rest>
void printAll(const T& first, const Rest&... rest) {
    std::cout << first << " ";
    printAll(rest...);
}

```

-   Използваме `typename... Rest` за parameter pack
    
-   Рекурсивно разопаковане
    

----------

## Нетипови параметри (Non-type Template Parameters)

```cpp
template <typename T, size_t N>
class StaticArray {
private:
    T data[N];
public:
    constexpr size_t size() const { return N; }
};

```

-   `N` е константа, известна по време на компилация
    

----------

## Шаблони и наследяване

### Наследяване от клас шаблон

```cpp
template <typename T>
class Base {
public:
    void foo(const T& x) { /* ... */ }
};

class Derived : public Base<int> {
public:
    void bar() { foo(42); }
};
```

### Шаблонен клас наследяващ друг шаблонен клас

```cpp
template <typename T>
class Derived : public Base<T> {
public:
    void bar(const T& x) { this->foo(x); }
};
```


### Задача
Напишете шаблонен клас GenericContainer, който съдържа масив с **фиксирана** дължина от подадения тип. Създайте два класа наследници: - Indexable, който имплементира оператор[]. - Resizeable, който позволява вмъкване на произволен индекс, като ако е извън рамките на масива, той трябва да се оразмери. Реализирайте клас наследник Vector на Indexable и Resizeable, който поддържа и член-функциите: - push_back(T& el) - вмъква подадения елемент в края на масива - push_front(T& el) - вмъква подадения елемент в началото на масива - pop_back() - премахва елемента в края на масива - pop_front() - премахва елемента в началото на масива Осигурете безопасна работа с класовете и добавете подходящи изключения, където смятате, че са необходими.