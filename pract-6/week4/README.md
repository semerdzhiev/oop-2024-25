# Потоци, файлове, предефиниране на оператори

## Потоци

![йерархия на класовете за потоци](https://cplusplus.com/img/iostream.gif)

Потоците са последователност от байтове. Ще разгледаме два вида потоци - входни (istream) и изходни (ostream).

Вече сме добре запознати с два такива - cin (входен) и cout (изходен) от библиотеката \<iostream>.

```c++
#include <iostream>

int main() {
    // входни операции

    // чете един символ от потока и го записва в символа c
    std::cin.get(char c); 

    // чете n символа от потока и ги записва в buff, като спира по-рано ако срещне символ за нов ред (най-често '\n') или знакът separator
    // забележете, че размерът на buff е n + 1, тъй като трябва да има място за терминиращата нула
    std::cin.getline(char buff[n + 1], size_t n, char separator = '\n') 

    // чете n символа от потока и ги записва в buff, като не прави проверки за терминираща нула и не я поставя в края му.
    std::cin.read(char buff[n + 1], size_t n);

    std::cin >> <променлива>;

    // изходни операции

    // записва символ c в потока
    std::cout.put(char c);

    // чете n символа от buff и ги записва в потока, като не прави проверки за терминираща нула
    std::cout.write(char buff[n + 1], size_t n);

    std::cout << <данни>;
}
```

## Файлове

За входно-изходни операции с файлове ще използваме така наречените файлови потоци. За целта ще използваме библиотеките \<ifstream> и \<ofstream> (за съответно входни и изходни операции), или само библиотеката \<fstream> (която съдържа другите две).

Задължително след отваряне на файл той трябва да се затвори.

```c++
#include <fstream> // не забравяйте да я включите

int main() {
    std::fstream file("fileName.txt");

    // проверка дали файлът е отворен успешно
    // не я забравяйте!!
    if(!file.is_open()) {
        std::cout << "Error!" << std::endl;
        return -1;
    }

    // ...

    file.close(); // !!!!
}
```

### get и put указатели

При извличане или записване на данни в поток съответно get и put указателите се местят напред.

### Състояние на поток

При работа с потока може да се активират следните флагове за неговото състояние:

- good - Всички операции са успешни
- bad - Загуба на информация
- eof - Краят на файла е достигнат
- fail - Последната операция е невалидна

При извикване на функциите със съответните имена се връща булева стойност, която обозначава дали флагът е активиран.

Функцията clear() изчиства състоянието на потока, като независимо от предишното му състояние флагът good ще връща истина

### Функции

```c++
#include <fstream>

int main() {
    std::fstream file("fileName.txt");

    if(!file.is_open()) {
        std::cout << "Error!" << std::endl;
        return -1;
    }

    // функции за потоци във входен режим
    
    // връща позицията, на която е get указателя
    int getPos = file.tellg();

    // премества get указателя на n-тата позиция след текущата му позиция
    file.seekg(n, std::ios::cur);  

    // премества get указателя на n-тата позиция от началото на потока
    file.seekg(n, std::ios::beg);

    // премества get указателя на n-тата позиция от края на потока 
    file.seekg(n, std::ios::end);  

    // функции за потоци в изходен режим
    // (аналогични на тези за входен, но с put указател)

    int putPos = file.tellp();
    file.seekp(n, std::ios::cur);
    file.seekp(n, std::ios::beg);
    file.seekp(n, std::ios::end);

    file.close();
}
```

Пример за четене на цял файл и извеждането му в потока cout:

```c++
#include <fstream>

const unsigned BUFF_SIZE = 1024;

int main() {
    std::ifstream file("fileName.txt");

    if(!file.is_open()) {
        std::cout << "Error!" << std::endl;
        return -1;
    }

    // буфер за данните при четене
    char buff[BUFF_SIZE];

    // четем, докато не стигнем края на файла
    while (!file.eof()) {
        file.getline(buff, BUFF_SIZE);
        std::cout << buff << std::endl;
    }
    
    file.close();
}
```

### Режими на работа

|ios|Резултат||
|-|-|-|
|ios::in (**in**put)|Отваря файл с възможност за входни операции|1|
|ios::out (**out**put)|Отваря файл с възможност за изходни операции, като изтрива съдържанието на файла, ако той съществува|2|
|ios::ate (**at e**nd)|get указателят се поставя в края на файла|4|
|ios::app (**app**end)|put указателят се поставя в края на файла|8|
|ios::trunc (**trunc**ate)|Ако файлът съществува, съдържанието му се изтрива|16|
|ios::binary (**binary**)|Отваря файлът в двоичен режим|32|

```c++
int main() {
    std::fstream inFile("fileName.txt", std::ios::in); 
    // пример за задаване на режим за работа

    std::fstream outFile("fileName.txt", std::ios::out | std::ios::app); 
    // отваряне на изходен файл със запазване на предишното съдържание

    std::fstream binaryFile("fileName.dat", std::ios::out | std::ios::binary | std::ios::ate); 
    // отваряне на изходен двоичен файл с get указател в края на файла
}
```

### Двоични файлове

За разлика от текстовите файлове, които разглеждахме досега, двоичните файлове съхраняват данните си във формат, който ние не можем да четем лесно.

Често използвано файлово разширение за тях е '.dat'.

Пример за записване на число num в бинарен файл:

```c++
#include <fstream>

int main() {
    std::ofstream file("fileName.dat", std::ios::binary);
    
    if(!file.is_open()) {
        std::cout << "Error!" << std::endl;
        return -1;
    }

    int num;
    std::cin >> num;

    // преобразуваме двоичните данни на num в константен низ, тъй като write не приема променливи от друг тип
    file.write((const char*)&num, sizeof(num));

    file.close();
}
```

Пример за четене на число num от бинарен файл:

```c++
#include <fstream>

int main() {
    std::ifstream file("fileName.dat", std::ios::binary);
    
    if(!file.is_open()) {
        std::cout << "Error!" << std::endl;
        return -1;
    }

    int num;

    // записваме данните в бинарния файл в променливата под формата на низ, но това не е проблем
    file.read((char*)&num, sizeof(num));    

    file.close();
}
```

## Оператори

### Предефиниране на оператори

Операторите имат:

- приоритет
- асоциативност
- позиция спрямо аргумента - префиксна / инфиксна / постфиксна

Можем да предефинираме следните оператори:

- аритметични (+, -, *, /, %)
- логически (!, &&, ||)
- указателни (&, *, ->, [])
- за сравнение (==, !=, <, >, <=, >=)
- побитови (&, |, ˆ, ˜, <<, >>)
- за присвояване (=, +=, -=, *=, /=, %=, &=, |= , <<=, >>=, ++, --)
- за работа с паметта (new, new[], delete, delete[])
- оператор за изброяване (,)
- оператор за извикване на функция (())
- оператор за преобразуване на тип

...но не и:

- тернарен оператор (? :)
- оператор за указване на област (scope resolution operator) (::)
- оператор за избор на член (.)
- оператор за намиране на големина (sizeof)
- препроцесорни оператори (#, ##)

*При предефиниране не се променят приоритетът и асоциативността на операторите, както и броят / позицията на аргументите им.

```c++
class ComplexNumber {
    double real;
    double im;

    ComplexNumber(double real, double im) : real(real), im(im) {};

    ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs) {
        ComplexNumber res = ComplexNumber(lhs.real + rhs.real, lhs.im + rhs.im);
        return res;
    }

    bool operator==(const ComplexNumber& other) {
        return this->real == rhs.real && this->im == rhs.im;
    }
}
```

### Предефиниране на оператори за потоци

```c++
class Person {
    char* name;
    unsigned age;

    // Constructor, Destructor, Copy constructor, operator=

public:
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& complex) {
	return os << person.name << " " << person.age;
}
```

#### Приятелски функции и класове

Приятелските функции / класове на даден клас имат достъп до всички негови компоненти (дори и тези, които са private!)

- friend \<name>([args]);
- friend class \<name>;

## Задачи

### Задача 1

Напишете функция, която приема име на текстов файл и естествено число n и записва числата от 0 до n в него.

### Задача 2

Напишете програма, която отпечатва кода си.

### Задача 3

Реализирайте функция, която приема име на текстов файл и два символа и заменя всяко срещане на първия символ с втория.

### Задача 4

Създайте функция, която по име на текстов файл извежда броя на непразните символи в него.

### Задача 5

Напишете функция, която приема два файла и записва съдържанието на първия в края на втория.

### Задача 6

Създайте клас Matrix, който реализира n x m матрица от цели числа.

Класът трябва да има два конструктора - Matrix(size_t n, size_t m) и Matrix(size_t n, size_t m, const int\*\* data), като n и m са положителни числа, както и деструктор, копиращ конструктор и operator=.

Предефинирайте следните оператори, които поддържат познатите ви операции с матрици:

- Оператор за събиране
- Оператор за изваждане
- Оператор за умножение (ако операцията е невалидна да се изведе подходящо съобщение и да се върне същата матрица)
- Оператор за вход от поток
- Оператор за изход към поток

Добавете към класа член-функциите readFromFile(const char\* fileName) и writeToFile(const char\* fileName), които четат от и записват стойностите на матрицата в текстов файл с подаденото име.
