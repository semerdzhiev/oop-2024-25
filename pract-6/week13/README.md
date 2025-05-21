﻿# Статично и динамично свързване. Виртуални функции. Полиморфизъм. Абстрактни класове.
#### Статично и динамично свързване. Виртуални функции.
Пример за **статично** свързване:
```c++
#include <iostream>
using namespace std;

struct A
{ 
    void f() const 
    {
	std::cout << "A::f()" << std::endl;
    }	
};

struct B : public A
{
    void f() const 
    {
	std::cout << "B::f()" << std::endl;
    }	
};

int main()
{
	B* bPtr = new B();

	A* aPtr = bPtr;
	
	bPtr->f(); // B::f()
	aPtr->f(); // A::f()
	
	delete bPtr;
}
 ```

 - **Статично** свързване - изборът на функцията, която трябва да се изпълни става **по време на компилация**.
 - **Динамично** свързване – изборът на функцията, която трябва да се изпълни става **по време на изпълнение на програмата**.

```c++
#include <iostream>
using namespace std;

struct A
{
    virtual void f() const 
    {
	std::cout << "A::f()" << std::endl;
    }	
};

struct B : public A
{
    void f() const 
    {
       std::cout << "B::f()" << std::endl;
    }	
};

struct C : public A
{
    void f() const 
    {
       std::cout << "C::f()" << std::endl;
    }	
};

int main()
{
	A* ptrs[3];
	A obj1;
	B obj2;
	C obj3;
	
	ptrs[0] = &obj1;
	ptrs[1] = &obj2;
	ptrs[2] = &obj3;
	
	ptrs[0]->f(); // A::f()
	ptrs[1]->f(); // B::f()
	ptrs[2]->f(); // C::f()
}
 ```
#### Полиморфизъм
Едни и същи действия се реализират по различен начин в
зависимост от обектите, върху които се прилагат.

 - Действията се наричат полиморфни.
 - Реализира се чрез виртуални функции.
 - Класовете, върху които ще се прилага, трябва да имат общ родител или прародител, т.е. да са наследници на един и същ клас.
 - В класа се дефинира виртуален метод, съответстващ на полиморфното действие.
 - Всеки клас предефинира или не виртуалния метод.
 -  Активирането става чрез указател към базов клас, на който може да се присвоят адресите на обекти на който и да е от базовите класове от йерархията

**Важно!** При полиморфна йерархия ще изтриваме обектите чрез указатели от базовия клас. За да се извикват правилните деструкори задължително **деструкторът на базовият клас** трябва е деклариран като виртуален!
```c++
#include<iostream>

struct Animal
{
	virtual void sayHello() const
	{
		std::cout << "Hello, I am a random animal" << std::endl;
	}

	virtual ~Animal(){} //!!!
};
struct Dog : public Animal
{
	void sayHello() const override
	{
		std::cout << "Hello, I am a dog!" << std::endl;
	}
};

struct Cat : public Animal
{
	void sayHello() const override
	{
		std::cout << "Hello, I am a cat!" << std::endl;
	}
};

struct Mouse : public Animal
{
};

int main()
{
	Animal** animals = new Animal*[3];

	animals[0] = new Dog();
	animals[1] = new Cat();
	animals[2] = new Mouse();


	//from base-class pointer
	animals[0]->sayHello(); // Hello, I am a dog!
	animals[1]->sayHello(); // Hello, I am a cat!
	animals[2]->sayHello(); // Hello, I am a random animal!

	delete animals[0], animals[1], animals[2];
	delete[] animals;
}

 ```
 #### Абстрактен клас
 

 - Чисто виртуална функция (**pure virtual function**) - виртуална функция без тяло.
 - Клас е **абстрактен**, ако в него има поне една **чисто виртуална функция**.

Тогава класът е предназначен единствено за наследяване и няма да може да създаваме обекти от него.
Така във всеки наследник ще трябва да се разпише имплементация на функцията. Ако някой наследник няма собствена имплементация, то и той става абстрактен клас.

```c++
#include<iostream>

struct Animal
{
	virtual void sayHello() const = 0;


	virtual ~Animal(){} //!!!
};
struct Dog : public Animal
{
	void sayHello() const override
	{
		std::cout << "Hello, I am a dog!" << std::endl;
	}
};

struct Cat : public Animal
{
	void sayHello() const override
	{
		std::cout << "Hello, I am a cat!" << std::endl;
	}
};

struct Mouse : public Animal
{
	void sayHello() const override
	{
		std::cout << "Hello, I am a mouse!" << std::endl;
	}
};

struct PrehistoricAnimal : public Animal
{};

int main()
{
	// Animal* pa1 = new Animal(); No! Animal is an abstract class!
	// Animal* pa2 = new PrehistoricAnimal(); No! PrehistoricAnimal is also an abstract class!

	Animal** animals = new Animal*[3];

	animals[0] = new Dog();
	animals[1] = new Cat();
	animals[2] = new Mouse();


	//from base-class pointer
	animals[0]->sayHello(); // Hello, I am a dog!
	animals[1]->sayHello(); // Hello, I am a cat!
	animals[2]->sayHello(); // Hello, I am a mouse!

	delete animals[0]
	delete animals[1]
	delete animals[2];
	delete[] animals;
}

 ```


# Виртуални таблици. Ключови думи override и final. Колекции от обекти в полиморфна йерархия. Копиране и триене.
## Виртуални таблици.

Виртуални таблици - таблица с указатели към функции. 

```c++
struct A
{
	virtual int f()
	{
		return 1;
	}
	virtual int g()
	{
		return 1;
	}
};

struct B : public A
{
	int f() override
	{
		return 2;
	}
};

struct C : public B
{
	int f() override
	{
		return 3;
	} 
	int g() override
	{
		return 3;
	}
};


 ```


![enter image description here](https://i.ibb.co/dbzJTtm/vtable-2-1.png)

## override и final
 - override указва, че дадена функция презаписва функция от базовия клас. Ако в базовия клас няма такава функция, то кодът няма да се компилира.
 - final указва, че дадена функция не може да се презависва надолу по йерархията или че даден клас не може да се наследява.


## Задачи
 
### Задача 1
 
Създайте абстрактен клас Shape, който имплементира член-функциите double area() и double perimeter(), както и void printInfo(), която извежда информация за фигурата - брой страни и техните дължини, лице и обиколка.
 
Реализирайте негови класове наследници Triangle, Square и Circle.
 
### Задача 2
 
Реализирайте абстрактен клас Employee, който съдържа член-данните име (низ с *произволна* дължина) и възраст, както и член-функцията double calculateSalary(), която пресмята месечната заплата на работника.
 
Създайте негови класове наследници със следните член-данни:
 
- FullTimeEmployee
    - int workDays - брой работни дни в месеца
    - int dailySalary - заплащане на работен ден
- PartTimeEmployee
    - double workHours - брой работни часове в месеца
    - double hourlySalary - заплащане на час
 
Създайте клас Company, който съдържа масив с произволна дължина от работници и член-функцията double totalSalaries(), която пресмята колко плаща общо фирмата на работниците си всеки месец.


##Присъстват материали, взаимствани от github хранилището на Ангел Димитриев