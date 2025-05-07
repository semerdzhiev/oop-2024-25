# Наследяване

Ако имаме клас, който споделя компоненти и/или поведение с вече съществуващ такъв,
то вместо да ги дефинираме наново, може да направим първия *наследник* на втория.

Наследникът съдържа всички член-данни и член-функции на родителския клас, които не са private.

Ако искаме дадени член-данни да се наследяват, но да няма външен достъп до тях,
можем да използваме модификатора за достъп *protected*.

Пример:

```c++
#include <iostream>

class Person {
  char* name;
  char[11] ucn;
  
protected:
  size_t age;
  
public:
  // getters / setters...  
};

class Student : public Person {

protected:
  char* fn;
  
public:
  // getters / setters...
};
```

Тук Student няма да има директен достъп до name и ucn, но ще има до age.

## Видове наследяване

- private - всички член-данни стават private в наследения клас
- protected - всички член-данни стават protected в наследения клас
- public - всички член-данни запазват модификатора си за достъп

При класовете наследяването е private по подразбиране, а при структурите е public.

## Параметри на функции

```c++
class Parent {
public:
  int a = 0;
};

class Child : public Parent {
public:
  int b = 0;
};

void funcA(Parent& p) {
  p.a++;
};
void funcB(Child& c) {
  c.b++;
};

int main() {
  Parent parent;
  Child child;
  
  funcA(parent); // a = 1
  funcB(parent); // грешка!
  
  funcA(child); // a = 1
  funcB(child); // b = 1
}
```

## Конструктори, деструктори и оператори за присвояване

Във всеки конструктор на наследника трябва да се указва кой конструктор на базовия клас да се извика.
Ако не е указано, то ще се извика конструкторът по подразбиране на родителя.

В двата случая първо ще се извика този на базовия клас, а след това на наследника.

При деструкторите е обратното - при унищожаване на наследника първо се извиква неговият и след това на базовият.

```c++
class Parent {
public:
  Parent() {
    std::cout << "Parent constructor" << std::endl;
  }
  
  ~Parent() {
    std::cout << "Parent destructor" << std::endl;  
  }
};
class Child : public Parent {
public:
  Child() : Parent() {
    std::cout << "Child constructor" << std::endl;
  }

  ~Child() {
    std::cout << "Child destructor" << std::endl;
  }  
};

int main() {
  Child child;
}

// Output:
// Parent constructor
// Child constructor
// Child destructor
// Parent destructor
```

При copy конструктора и оператора за присвояване на наследника викаме експлицитно съответните на родителския клас.

```c++
Child::Child(const Child& other) : Parent(other) {
  // тук копираме само член-данните, които добавяме в наследника
}

Child& Child::operator=(const Child& other) {
  if (this != &other) {
    Parent::operator=(other);
    
    // обичайните за operator= неща, като трием и копираме само новите член-данни
  }
  return *this;
}
```