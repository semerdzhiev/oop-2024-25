<h1>Конструктори, част 2; Инициализиращ списък; Копиращ конструктор и оператор=;Динамични данни в структури;</h1>


**<h2>Default constructor vs param constructors</h2>**

Когато нямаме дефиниран нито един конструктор, компилатора сам създава конструктор по подразбиране. Когато имаме дефиниран поне един конструкотр (независимо с параметри или не) компилаторът спира да създава конструктор по подразбиране сам и трябва да използваме вече дефинираните от нас.

```c++
struct S {
    int n;
    S();
    S(int);
};

S::S() {
    n = 0;      // S::n бива занулен.
}

S::S(int n) {
    this->n = n; // S::n взима стойността на параметъра n.
}

int main() {
    S s;        // Извиква S::S()
    S s2(10);   // Извиква S::S(int)
}
```
<br>
---

**<h2>Инициализиращ списък</h2>**

Специална синтактична форма за инициализиране на не-дефолтните променливи на класа. Синтактично представлява двуеточие (:), последвано от списък разделен със запетайки (,) от изброени member-initializers:

```c++
struct S {
    int n;
    S(int);       // Декларация на параметризиран конструктор
    S() : n(7) {} // Дефиниция на конструктор по подразбиране:
                    // ": n(7)" инициализиращ списък.
};

S::S(int x) : n{x} {} // Дефиниция на параметризиран конструктор: ": n{x}" инициализиращ списък

int main() {
    S s;      // Извиква S::S()
    S s2(10); // Извиква S::S(int)
}
```

Ако не статично поле има инциализираща стойност по подразбиране и се появява в инициализиращият списък, тогава стойността по подразбиране се игнорира и стойността от инциализиращият списък се използва:

```c++

struct S {
	int n = 42;  // Инициализираща стойност по подразбиране.
	S() : n(7) {} // Задава стойността на n да е 7.
};

```

Членове референции не мога да бъдат обвързани с временни обекти, в инциализиращият списък:

```c++

struct A {
	A() : v(42) {} // Error
}
```

***!!!Променливите се инициализират в реда на тяхната декларация, независимо от реда им на изброяване в инициализиращия спиък!!!***

```c++
struct Foo
{
    int i;
    double d;
    float f;

    Foo(): f{4.2}, d{3,14}, i{69} {} // i will be initialized first, after that d and lastly f
};
```
  
---
**<h2>Копиращ конструктор и оператор за присвоявяне (=)</h2>**

Заедно с конструктора по подразбиране и деструктора във всеки клас се дефинират и следните член-функции:

-   **Копиращ конструктор** – специален конструктор, който приема обект от същия клас и създава негово точно копие.
-   **Оператор =** – функция/оператор, който приема обект от същия клас и актуализира данните на вече съществуващ обект (този, от който е извикана функцията).

Ако копиращият конструктор и/или операторът = не са изрично дефинирани, компилаторът автоматично генерира техни версии по подразбиране.


```c++
#include <iostream>

struct Test {
    Test() {
        std::cout << "Default constructor\n";
    }

    Test(const Test& other) {
        std::cout << "Copy constructor\n";
    }

    Test& operator=(const Test& other) {
        std::cout << "operator=\n";
	    return *this;
    }

    ~Test() {
        std::cout << "Destructor\n";
    }
};

void f(Test object) {
    //do Stuff
}

void g(Test& object) {
    //do Stuff
}

int main()
{
    Test t;      //Default constructor;

    Test t2(t);  // Copy constructor
    Test t3(t2); // Copy constructor	
    t2 = t3;     // operator=
    t3 = t;      // operator=

    Test newTest = t; //Copy constructor !!!!!!!

    f(t);   // Copy constructor	
    g(t);   // nothing. We are passing it as a reference. We are not copying it!

    Test* ptr = new Test();  // Default constructor // we create a new object in the dynamic memory. The destructor must be invoked explicitly  (with delete)

    delete ptr; // Destructor	

} //Destructor Destructor Destructor Destructor
```


---
<br>

<h2>Как работят дефинираните от компилатора функции?</h2>

Всяка една от тези функции **извиква 'рекурсивно' същите функции върху член-данните.**

#### Пример за конструктора по подразбиране:

![enter image description here](https://i.ibb.co/smKkDpJ/def-constr.png)

#### Пример за деструктора:

![enter image description here](https://i.ibb.co/qNHfSTL/def-constr.png)

  

#### Пример за копиращия конструктор:

![enter image description here](https://i.ibb.co/QmCh9z6/cc.png)


---
<br>

<h2> Проблем при функциите, генерирани от компилатора:</h2>
  

Да разгледаме следния код:
```c++
struct  Person {
public:
	PersonA(const char* name, int age) {
		this->name = new  char[strlen(name) + 1];
		strcpy(this->name, name);
		this->age = age;
	}
private:
	char* name;
	int age;
};

int main() {
	Person p1;
	Person p2(p1);
}
```

Горното извикване на копиращия конструктор има **неправилно поведение**:



![enter image description here](https://i.ibb.co/q5rfGBf/Capture.png)

  
  

Това е **shallow copy**. В p2 са се копирали стойностите на p1, което довежда до споделяне на една и съща динамична памет.

В тази ситуация ще трябва да се имплементират експлицитно **копиращия конструктор, оператора за присвояване и деструктора**, защото генерираните от компилатора не биха работили правилно.

  

**Правилното поведение** на копиращия конструктор е следното:

  

![enter image description here](https://i.ibb.co/XZq5rGT/33.png)


---
<br>

<h2>Конструктор и деструктор при обекти с динамична памет</h2>

```c++
#include <iostream>

struct Test {
	Test() {
		std::cout << "Object is created" << std::endl;
		name = new char[10]; // Заделяме паметта при създаване на обекта.
	}

	~Test() {
		std::cout << "Object is destroyed" << std::endl;
		delete[] name; // Изчистваме паметта, когато обектът "умре".
	}

private:
	int a;
	char* name;
};

int main() {
	while (..) {
		Test t;// Object is created 
		if () {
			Test t2; // Object is created 

		}// Object is destroyed (t2)

	}//Object is destroyed (t)
}
```

---
<br>

**Задача 1:** Създайте клас Beer, който има две полета - марка и количество в милилитри. Напишете параметризиран конструктор. Също така да се следват принципите на капсулацията. Да се реализират следните функционалности на класа:

Напишете get методи за марката и количеството на бирата.
Напишете метод, който добавя една бира към друга.
Напишете метод, който допълва бирата с дадени милилитри.
Напишете метод, който проверява дали дадена бира съдържа каквото и да е количество от дадена марка.

**Пример за работа:**
beer1 - Corona, 500ml
beer2 - Heineken, 500ml

beer1.add(beer2, 250);

beer1 - Corona&Heineken, 750ml beer2 - Heineken, 250ml

beer1.check("Heineken") - true beer1.check("Stella Artois") - false beer1.check(beer2.getName()) - true

---


**Задача 2:** Да се реализира клас, който представя сума на масив от числа по следният начин: 3^0 + 7^1 + 2^3 + ... k^(n-1). Да се създадът два конструктора, един по подразбиране, който да слага големината на масива на 10 и един параметричен, на който ще се подава колко елемента искаме да е масива.

**Пример за работа:**
sumator.add(4); sumator.add(2);

sumator.getSum(); - 3

sumator.add(5);

sumator.getSum(); - 28

sumator.removeLast();

sumator.getSum(); - 3

sumator.changeAt(5, 1);

sumator.getSum();

##Присъстват материали, взаимствани от github хранилището на Ангел Димитриев