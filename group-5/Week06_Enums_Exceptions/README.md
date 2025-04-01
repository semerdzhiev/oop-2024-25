# Изключения (Exceptions)

<h3>Изключения</h3>

Ключовата дума `throw` прекратява изпълнението на текущата функция/метод и започва процеса по разгъване на стека. Докато прави така нареченият *"Stack unwinding"* програмата извиква деструкторите на всички обекти в стековата рамка на функцията, в която се намира. Този процес продължава, докато грешката не бъде хваната или докато не терминира main функцията, с което и програмата.

```c++
int main()
{
    throw 20; // terminate called after throwing an instance of 'int'
}
```

**!!!Важно!!!**

1. При разгъване на стековата рамка може да се пренася само по 1 грешка в даден момент от време. Ако станат повече от 1 програмата директно се терминира, дори и обработваме грешките, някъде по-надолу в стека.

2. Никога не хвърляме грешка в деструктора на някой клас!!!
    - Хвърляйки грешка в деструктора на някой обект може да се появи следната ситуация:
        main -> f -> g.
        В f сме създали обект от тип T и той хвърля грешка от тип int в деструктора си.
        g хвърля грешка от тип char.
        В процеса на разгъване на стека g бива терминирана, след което и f, но f извиква деструктора на обекта от тип T, с което стават две различни грешки, които трябва да бъдат предадени и обработени.
        Програмата обаче не може да се ориентира, коя грешка е по-важна, с което прекратява нашата програма.

3. Ако хвърлим грешка в конструктора, на някой обект, то този обект няма да бъде създаден изобщо, но е хубаво преди да я хвърлим да освободим динамичната памет, която сме заделили.

## Хвърляне на изключение

За да бъде сигнализирано за възникването на определена неочаквана ситуация, различна от това, което програмата може да обработи, се използва следната конструкция:  
**throw <израз>;**  
<израз> е съобщението към външния свят и може да бъде от произволен тип. Обикновено това е код на грешка (константа от изброен тип), символен низ с описание на грешката, може да бъде дори обект от потребителски дефиниран тип.  

**Примери:**  
```cpp
throw INVALID_INDEX;  
throw “Index out of range!”;  
throw InvalidStudentsIDException();
```
<h3>try & catch</h3>

- В try блока пишем код който потенциално може да хвърли грешка.
- В catch блока хващаме грешките хвърлени от try блока и ги обработваме.

Можем да слагаме няколко catch блока един след друг с различни параметри.
Като накрая можем да сложим блокът `catch(...)`, който хваща всички останали изключения.

```c++
#include <iostream>

int main(){
    try
    {
        throw 20;
    }
    catch(int e)
    {
        std::cout << "Exception occurred exception code: " << e << '\n';
    }
    catch(char const *c)
    {
        std::cout << "Exception occurred: " << e << '\n';
    }
	catch(...)
	{
        std::cout << "Exception occurred!\n";
	}
}
```

<h3>Видове грешки</h3>

Стандартната библиотека за грешки `exception`. В нея има различни видове грешки, които можете да разгледате [тук](https://en.cppreference.com/w/cpp/error/exception).

```c++
#include <iostream>
#include <exception>

int main()
{
    try
    {
        throw std::invalid_argument("Exception occurred");
    }
    catch(const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}
```

## Прихващане на изключения

Ключовата дума **try** се използва, за да дефинира блок от операции, който ще бъде наблюдаван за възникване на изключения. Всяка операция в рамките на блока се проверява. Ако възникне изключение, то се прихваща само ако **try блокът** е последван от **catch блок** с тип, съответстващ на възникналото изключение. Всеки try блок трябва да има поне един catch блок, а може и да е последвано от няколко такива.  

**Пример:**  
```c++
std::cout << "Before the try block..." << std::endl;
try
{
	std::cout << "Inside the try block, before the throw..." << std::endl;
	throw "Error"; // изключението е от тип символен низ
	std::cout << "Inside the try block, after the throw..." << std::endl;
}
catch (const char* expr) // това, което е обявено като тип в catch блока трябва да съвпада с типа на изключението
{
	std::cerr << "Exception caught: " << expr << std::endl;
}
std::cout << "After the try block, after the throw..." << std::endl;
```

- Ако в тялото на try блока **не възникне изключение**, всички catch блокове се игнорират и изпълнението продължава от първата операция след последния catch блок.
- Ако в тялото на try блока **възникне изключение**, което няма съответстващ catch блок или възникне изключение извън try блок, съдържащата го функция (т.е. функцията, в която е възникнало изключението) прекъсва, при което всички локални променливи се освобождават и програмата се опитва да намери try блок в извикващата функция. Извършва се **изкачване по стека (stack unwinding)**.  

```c++
struct MyObject
{
    MyObject()
    {
        std::cout << "MyObject constructor called" << std::endl;
    }
    ~MyObject()
    {
        std::cout << "MyObject destructor called" << std::endl;
    }
};

int main()
{
    try
    {
        MyObject obj1;
        MyObject obj2;
        throw "An exception occurred";
        MyObject obj3;
    }
    catch (const char* e)
    {
        std::cout << "Exception caught: " << e << std::endl;
    }
}
```

### Изключения в конструкторите

Ако конструктор не успее по някаква причина да създаде валиден обект, например при подадени некоректни стойности за член-данните, може да се хвърли изключение, с което да се сигнализира, че обектът не е създаден успешно.  

При възникване на грешка в конструктор, **деструкторът на класа не се извиква** :bangbang:  
Следователно не може да се разчита на него да освободи външни ресурси, ангажирани преди възникването на грешката. 
**Освобождаването на тези ресурси трябва да се осъществи преди хвърлянето на изключението**. Ако в класа има вградени обекти от други класове, за тях ще бъдат извикани деструктори.
```c++
class Item
{
private:
	char* name;
	char id[6];
	double price;
	
public:
	Item(const char* id, const char* name, double price);
	Item(const Item& other);
	Item& operator=(const Item& other);
	~Item();
	// ...
};

Item::Item(const char* name, const char* id, double price)
{
	if (name == nullptr)
	{
		throw "Invalid name!";
	}
	// ако паметта за името е заделена първо
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);

	if (!isValid(id)) 
	{
		// трябва да се освободи паметта за името преди да се хвърли изключение
		delete[] this->name;
		throw "Invalid id!";
	}
	strcpy(this->id, id);

	if (price < 0)
	{
		delete[] this->name;
		throw "Invalid price!";
	}
	this->price = price;
}
```

По- изчистена реализация на същата функция:
```c++
Item::Item(const char* name, const char* id, double newPrice){
	if (!isValid(id))
	{
		throw "Invalid id!";
	}
	strcpy(this->id, id);

	if (price < 0)
	{
		throw "Invalid price!";
	}
	this->price = price;

	// може името да се обработи последно 
	if (name == nullptr)
	{
		throw "Invalid name!";
	}
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}
```

### Изключения в деструкторите

Изключенията не трябва да напускат деструкторите. Ако възникне изключение в деструктора, то трябва да се прихване и да се обработи, ако е възможно да бъдат освободени всички заделени външни ресурси. Проблемът при възникване на изключение в деструктор е, че при превъртането на стека при обработка на изключение се извикват деструкторите на всички локални обекти. Ако от такъв деструктор възникне изключение, то компилаторът не е в състояние да обработи новото изключение успоредно с текущото и възниква конфликт. В крайна сметка, програмата ще бъде прекъсната веднага без възможност за обработка.

---

## Нива на сигурност при изключенията

Съществуват няколко различни нива на сигурност при възникване на изключение. 

### No-throw guarantee
Операциите винаги са успешни. Дори и да възникне някакво изключение, то се обработва вътрешно и външният свят не разбира за него. Пример за такава функция е преместващият конструктор.

### Силна сигурност (strong exception safety guarantee)
Операциите могат да пропаднат, но ако дадена операция пропадне, то няма да има странични ефекти от нея и обектът остава в оригиналното си състояние. Понякога се постига по-трудно.

### Слаба сигурност (weak/basic exception safety guarantee)
Частично изпълнение на операциите, което може да доведе до странични ефекти. Обектът е във валидно състояние, което може да е различно от първоначалното. Няма изтичане на ресурси.

### No exception safety
Няма никаква гаранция за състоянието на обектите и операциите.

---

Да допуснем, че възниква изключение при заделянето на памет за name:  

**Пример за basic exception safety guarantee:**
```c++
Item& Item::operator=(const Item& other)
{
	if (this != &other) 
	{
		this->setID(other.id);
		this->setPrice(other.price);
		this->setName(other.name);
	}
	return *this;
}
```

**Пример за strong exception safety guarantee:**
```c++
Item& Item::operator=(const Item& other)
{
	if (this != &other) 
	{
		this->setName(other.name);
		this->setID(other.id);
		this->setPrice(other.price);
	}
	return *this;
}
```

Още материали за грешките:
- https://www.learncpp.com/#:~:text=27.1,specifications%20and%20noexcept
- https://en.cppreference.com/w/cpp/error/exception

---
# [Енумерации (Enums)](https://en.cppreference.com/w/cpp/language/enum)

## Enum (plain enum)
**Примери:**
```c++
enum Color { Red, Green, Blue, Purple, Orange };
enum Animal { Dog, Deer, Cat, Bird };
```

### Проблеми при използването на plain enums:
1. Не можем да имаме два изброителни типа, които съдържат повтарящи се енумератори (допустими стойности):
```c++
enum Gender { Male, Female };
enum Gender2 { Male, Female }; // грешка, защото на горния ред вече сме дефинирали Male, Female
```

2. Не можем да създадем променлива с име, което вече съществува като енумератор в някой enum:
```c++
enum Gender { Male, Female };

int main()
{
	int Male = 5; // грешка
}
```

3. При plain enums имаме **имплицитно конвертиране към int**, което води до проблеми:
```c++
enum Color { Red, Green, Blue, Purple, Orange };
enum Animal { Dog, Deer, Cat, Bird };

int main()
{
    Color color = Color::Red; // Same as Color color = Red
    Animal animal = Animal::Bird;

    int num = color; // no problem

    if (color == Animal::Dog) // no problem (bad)
        std::cout << "Bad, states that red color is equal to dog" << std::endl;

    if (animal == Color::Purple) // no problem (bad)
        std::cout << "Bad, states that bird is equal to purple color" << std::endl;
}
```

## Enum class (scoped enumeration)
Енъм класовете са **strongly typed** и **strongly scoped**, което решава споменатите проблеми на plain enums.
```c++
enum class Color { Red, Green, Blue, Purple, Orange };
enum class Animal { Dog, Deer, Cat, Bird };

int main()
{
    Color color = Color::Red;
    Animal animal = Animal::Dog;

    // int num = color; // error
    int num2 = static_cast<int>(color); // no problem

    // if (color == animal) // error (good)
    //    std::cout << "Bad, states that red color is equal to dog" << std::endl;
}
```
Още материали за [enums](https://www.learncpp.com/#:~:text=13.1,enumerations%20(enum%20classes)).

---
## :pizza: Задача :pizza:
Ще направим имплементация, използвайки [Builder](https://refactoring.guru/design-patterns/builder) design pattern.

Създайте клас пица, която може да има:

- Размер (малък, среден, голям)
- Сос за основа: доматен, сметанов, трюфелов
- Топинги: маслини, чушки, гъби, лук
- Месни топинги: пеперони, пилешки хапки, аншоа, чоризо
- Сирена: моцарела, чедър, топено сирене, фета

Създайте клас pizza maker, с който лесно да може да се създава пица, той трябва да има методи като addTopping, addCheese, ...