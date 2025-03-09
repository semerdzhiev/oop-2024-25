# Конструктори, деструктори, Rule of Three

## Конструктор

Конструкторите са член-функции, чрез които се инициализират член-данните на обект от даден клас (структура). Те могат да бъдат **по подразбиране**, **с параметри** и **copy конструктор**.
## Copy конструктор

Създава нов обект като копие на друг вече съществуващ обект. Използва се при предаване по стойност, връщане от функция и инициализация.
## Деструктор

Деструкторите освобождават динамично заделената памет и други ресурси. Изпълняват се автоматично при унищожаване на обекта.
## Оператор за присвояване (`=`)

Използва се за копиране на стойностите от един съществуващ обект в друг. Важно е да се проверява за самоприсвояване (`this != &other`).

## Rule of Three

Ако клас използва динамично заделена памет, той трябва да дефинира:
1. **Copy конструктор**
2. **Оператор за присвояване (`=`)**
3. **Деструктор**

Ако клас използва динамично заделена памет, трябва да се дефинират всички от следните: Copy конструктор, Оператор за присвояване и Деструктор. Те гарантират правилното управление на ресурсите и предотвратяват проблеми като **memory leaks**.

**Пример:**

```cpp
#include <cstring>

class Student {
private:
    char* firstName;
    char* lastName;
    unsigned specialtyId;

    void freeMemory() {
        delete[] this->firstName;
        delete[] this->lastName;
        this->firstName = nullptr;
        this->lastName = nullptr;
    }

    void copy(const Student& other) {
        if (other.firstName) {
            this->firstName = new char[std::strlen(other.firstName) + 1];
            std::strcpy(this->firstName, other.firstName);
        } else {
            this->firstName = nullptr;
        }

        if (other.lastName) {
            this->lastName = new char[std::strlen(other.lastName) + 1];
            std::strcpy(this->lastName, other.lastName);
        } else {
            this->lastName = nullptr;
        }

        this->specialtyId = other.specialtyId;
    }

public:
 
    Student() : firstName(nullptr), lastName(nullptr), specialtyId(0) {}
    
    Student(const char* firstName, const char* lastName, unsigned specialtyId) {
        if (firstName) {
            this->firstName = new char[std::strlen(firstName) + 1];
            std::strcpy(this->firstName, firstName);
        } else {
            this->firstName = nullptr;
        }
        if (lastName) {
            this->lastName = new char[std::strlen(lastName) + 1];
            std::strcpy(this->lastName, lastName);
        } else {
            this->lastName = nullptr;
        }
        this->specialtyId = specialtyId;
    }

    ~Student() {
        freeMemory();
    }

    Student(const Student& other) {
        copy(other);
    }
    
    Student& operator=(const Student& other) {
        if (this != &other) {
            freeMemory();
            copy(other);
        }
        return *this;
    }
};


```

---

# Задача

Създайте система за управление на университетски курсове, като използвате два основни класа: `Student` (Студент) и `Course` (Курс).

### Клас Student (Студент)

**Полета:**
- `char* firstName` – динамичен низ за име на студента.
- `char* lastName` – динамичен низ за фамилия на студента.
- `unsigned specialtyId` – идентификатор на специалността.

**Функционалности:**
- Конструктор по подразбиране.
- Конструктор с параметри.
- Копиращ конструктор и оператор за копиращо присвояване (спазвайки правилата **rule-of-3**).
- Деструктор, който освобождава динамично заделената памет.
- Метод `void print() const` – отпечатва информация за студента във формат:
  `Name: <име> <фамилия>, Specialty ID: <номер>`.
- Метод `bool hasSameSpecialty(const Student& other) const` – проверява дали двама студенти са от една и съща специалност.
- Метод `void changeSpecialty(unsigned specialtyId)` – променя идентификатора на специалността на студента.

---

### Клас Course (Курс)

**Полета:**
- `char* courseName` – динамичен низ за име на курса.
- `char* courseCode` – динамичен низ за код на курса.
- `Student* students` – динамичен масив от обекти `Student`.
- `size_t studentCount` – текущ брой записани студенти.
- `size_t capacity` – максимален брой студенти в курса преди увеличаване на размера.

**Функционалности:**
- Конструктор по подразбиране.
- Конструктор с параметри.
- Копиращ конструктор и оператор за копиращо присвояване.
- Деструктор, който освобождава динамично заделената памет.
- Метод `void addStudent(const Student& newStudent)` – добавя студент към курса. Ако капацитетът е запълнен, разширява масива динамично.
- Метод void print() const – отпечатва информация за курса и всички записани студенти.
- Метод bool hasStudent(const char* firstName, const char* lastName) const – проверява дали даден студент е записан в курса, като търси студента по име и фамилия.
- Метод void removeStudent(const char* firstName, const char* lastName) – премахва студент от курса, като търси студента по име и фамилия.
- Метод Student* findStudentsBySpecialty(unsigned specialtyId, size_t& count) const – връща масив от студенти, които са от дадена специалност. Методът задава стойността на count на броя на намерените студенти.
- Метод size_t getStudentCount() const – връща броя на записаните студенти в курса (т.е. текущия брой студенти).
  
---



Създайте примерна програма (`main()`), която:
1. Създава курс с име и код.
2. Добавя няколко студента към курса.
3. Проверява дали даден студент е записан в курса.
4. Търси студенти по специалност.
5. Извежда информация за курса и студентите.

---
