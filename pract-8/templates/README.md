
# Templates в C++

Templates (шаблони) ни помагат да пишем „обобщени“ класове и функции, като предотвратяват дублирането на код и писането на излишни overloaded функции. 

> **Важно:** Не бъркайте C++ шаблони и generics (използвани в други езици като Java или C#)! Те работят различно по отношение на компилация и специализация.

---

## Шаблони на функции (Function Templates)

Function template позволява дефиниране на обща функция за множество типове данни:

```cpp
template <typename T>
void printArray(T* arr, int length) {
    for (int i = 0; i < length; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int ints[]    = {1, 2, 3};
    double dbls[] = {1.1, 2.2, 3.3};

    printArray(ints, 3);    // T -> int
    printArray(dbls, 3);    // T -> double
}
````

- Синтаксис: `template <typename T>` или `template <class T>`
- При извикване компилаторът **инстанцира** (генерира) специфична версия за подадения тип.
---

## Шаблони на класове (Class Templates)

Class template дефинира генеричен клас, който работи с произволен тип:

```cpp
template <typename T>
class Box {
private:
    T data;
public:
    Box(const T& value) : data(value) {}
    T get() const { return data; }
};

int main() {
    Box<int>    intBox(123);
    Box<double> dblBox(3.14);
    std::cout << intBox.get() << std::endl;
    std::cout << dblBox.get() << std::endl;
}
```

### Стойности по подразбиране за параметри на шаблона

```cpp
template <typename T = int, typename S = double>
class Pair {
public:
    T first;
    S second;
};

// По подразбиране: Pair<int, double>
Pair<>      p1;
Pair<char>  p2;   // T -> char, S -> double
Pair<float, float> p3;
```

### Alias Templates

Използваме `using` (или `typedef`) за създаване на удобни имена на специализации:

```cpp
template <typename T>
class Box { /* ... */ };

using IntegerBox = Box<int>;
// или:
typedef Box<int> IntegerBox;
```

---

## Специализация на шаблони (Template Specialization)

### Пълна специализация (Full Specialization)

Позволява конкретна реализация за указан тип:

```cpp
template <typename T>
class Printer {
public:
    static void print(const T& x) {
		 std::cout << x << std::endl; 
    }
};

// Специализация за char*
template <>
class Printer<char*> {
public:
    static void print(char* const& x) {
        std::cout << "C-string: " << x << std::endl;
    }
};
```

### Частична специализация (Partial Specialization)

Подходяща за класове, когато искаме алтернативно поведение при определена комбинация от параметри:

```cpp
template <typename K, typename V>
class Map { /* обща имплементация */ };

// Частична специализация, когато стойностите са bool
template <typename K>
class Map<K, bool> { /* ... */ };
```

### Специализация на член-функция

Можем да специализираме отделна функция на класов шаблон:

```cpp
template <typename T>
class Calculator {
public:
    T add(T a, T b) { return a + b; }

    // общ печат
    void print(const T& x) { std::cout << x << std::endl; }
};

// специализация само за int
template <>
void Calculator<int>::print(const int& x) {
    std::cout << "int value: " << x << std::endl;
}
```

---

## Variadic Templates

Позволяват произволен брой параметри:

```cpp
#include <iostream>

void printAll() {
    std::cout << std::endl;
}

template <typename T, typename... Rest>
void printAll(const T& first, const Rest&... rest) {
    std::cout << first << " ";
    printAll(rest...);
}

int main() {
    printAll(1, 2.5, "hello", 'c');
}
```

- `typename... Rest` дефинира parameter pack.
- Рекурсивното разопаковане гарантира извеждането на всички аргументи.

---

## Нетипови параметри (Non-type Template Parameters)

Можем да предаваме константни стойности:

```cpp
template <typename T, size_t N>
class StaticArray {
private:
    T data[N];
public:
    constexpr size_t size() const { return N; }
};

int main() {
    StaticArray<int, 10> arr;
    std::cout << arr.size(); // 10
}
```


---
# Шаблони и наследяване

Шаблоните и наследяването могат да се комбинират, за да се създадат гъвкави йерархии от класове. Основни моменти:

**Наследяване от клас шаблон:**
```cpp
    template <typename T>
    class Base {
    public:
        void foo(const T& x) { /* ... */ }
    };
    
    // Наследяване за конкретен тип
    class Derived : public Base<int> {
    public:
        void bar() { foo(42); }
    };
    ```

*При това базовият клас се инстанцира за T=int, и всички негови методи се наследяват.*

**Клас шаблон, наследяващ друг клас шаблон:**

```cpp
template <typename T>
class Base {
public:
	void foo(const T& x) { /* ... */ }
};

template <typename T>
class Derived : public Base<T> {
public:
	void bar(const T& x) { this->foo(x); }
};
```

*Използваме `this->foo(x)` или квалифицирано име (`Base<T>::foo(x)`), за да препратим към шаблонните член-функции на базовия клас.*

**Специализация и наследяване:** Ако специализираме базов клас, наследниците могат да се държат различно:
 
```cpp
template <typename T>
class Base { /* обща имплементация */ };

template <>
class Base<bool> { /* специална имплементация за bool */ };

template <typename T>
class Derived : public Base<T> { /* ... */ };

// Derived<bool> наследява специализираната версия Base<bool>
```


---

## Задача:

Създайте система за управление на артикули в склад, като всеки артикул може да бъде от различни категории. Всеки артикул има общи характеристики като **име** и **цена**, но за всяка категория има специфични допълнителни атрибути.

#### Видове артикули:

1. **Книги** – **автор**, **жанр**, **година на издаване**.
2. **Електронни устройства** – **марка**, **модел**, **гаранция** (в месеци), **дата на последно обновление**.
3. **Хранителни продукти** – **срок на годност** (в дни), **производител**.
### Изисквания:

1. **Базов клас `Item`**:
    - Съдържа **име** и **цена**.
    - Реализирайте **виртуални методи**:
        - `getName()`: връща името на артикула.
        - `getPrice()`: връща цената на артикула.
        - `printInfo()`: извежда информация за артикула.
    - Реализирайте **предефиниране на оператора за сравнение** (`operator<`) на базовия клас **`Item`**, който сравнява артикулите по цена.
2. **Наследници на `Item`**:
    - **Book**:
        - Полета: **автор**, **жанр**, **година на издаване**.
        - Предефинирайте метода `printInfo()` за извеждане на информация за книгата.
    - **Electronics**:
        - Полета: **марка**, **модел**, **гаранция**, **дата на последно обновление**.
        - Предефинирайте метода `printInfo()` за извеждане на информация за електронното устройство.
    - **FoodProduct**:
        - Полета: **срок на годност**, **производител**.
        - Предефинирайте метода `printInfo()` за извеждане на информация за хранителния продукт.
3. **Шаблонен клас `Inventory<T>`**:
    - Поддържа списък с артикули от тип `T`, където `T` наследява `Item`.
    - Функции:
        - `add(const T&)`: добавя артикул в склада.
        - `removeByName(const std::string&)`: премахва артикул по име.
        - `printAll()`: извежда информация за всички артикули.
        - `sortBy()`: сортира артикули по зададен критерий (лямбда функция).
4. **Шаблонна специализация**:
    - Създайте специализация на шаблона **`Inventory<Book>`**, която добавя:
        - Функция за намиране на най-старата книга в склада.
        - Функция за търсене на книги по жанр.