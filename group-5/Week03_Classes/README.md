# Методи (член-функции). Конструктори и деструктор. Капсулация. Гетъри и сетъри.

```c++

struct Student
{
    int age;
    float gpa;
    char* name;
};

void initialise(Student& student, int age, float gpa, const char* name)
{
    student.age = age;
    student.gpa = gpa;
    student.name = new char[strlen(name) + 1];
    strcpy(student.name, name);
}

void free(Student& student)
{
    delete[] student.name;
    student.name = nullptr;
}

void setAge(Student& student, int age)
{
    student.age = age;
}

int getAge(const Student& student)
{
    return student.age;
}

int main()
{
    Student student;
    initialise(student, 20, 3.5, "John");
    free(student);
}
```

Горният програмен фрагмент е валиден, но всички функции се отнасят до структурата Student. Можем да ги "групираме" като член-функции на класа.

## Методи (член-функции)

- Функции, които **не съществуват глобално**.
- Имената им са от вида **\<ClassName\>::\<memberFunctionName\>**
- **Работят с член-данните на инстанцията/обекта** от дадена структура/клас. Накратко, работят с данните на обекта.
- **Извикват се с инстанция/обект** на структурата/класа.
- Компилаторът преобразува всяка член-функция на дадена структура/клас в обикновена функция с уникално име и един допълнителен параметър – **константен указател към инстанцията/обекта**.

```c++
struct Student
{
    int age;
    float gpa;
    char* name;

    void initialise(int age, float gpa, const char* name)
    {
        this->age = age;
        this->gpa = gpa;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    void free()
    {
        delete[] name;
        name = nullptr;
    }

    void setAge(int age)
    {
        this->age = age;
    }

    int getAge() const
    {
        return age;
    }
};

int main()
{
    Student student;
    student.initialise(20, 3.5, "John");
    student.free();
}
```

### Концепция на this

Всяка член-функция скрито от нас получава като аргумент специална променлива (**this**) – **константен указател към текущия обект, с който функцията работи**.
Компилаторът преобразува член-функциите до следните глобални функции:

Компилаторът транслира всички извиквания на методи по следния начин.

p1.print(); → print(&p1);


```c++
void Student::setAge(Student* const this, int age)
{
    this->age = age;
}

int Student::getAge(const Student* const this)
{
    return this->age;
}
```

## Конструктори и деструктор

**Конструктор**:
- Извиква се при създаване на обекта.
- Има същото име като класа.

**Деструктор**:
- Извиква се при унищожаване на обекта.
- Има същото име като класа със символ '~' отпред.

```c++
struct Student
{
    int age;
    float gpa;
    char* name;

    Student(int age, float gpa, const char* name)
    {
        this->age = age;
        this->gpa = gpa;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    ~Student()
    {
        delete[] name;
    }
};

int main()
{
    Student student(20, 3.5, "John");
}
```

### Ред на работа на конструкторите и деструкторите

```c++
struct A
{
    A() { std::cout << "A()" << std::endl; }
    ~A() { std::cout << "~A()" << std::endl; }
};

struct B
{
    B() { std::cout << "B()" << std::endl; }
    ~B() { std::cout << "~B()" << std::endl; }
};

struct C
{
    A a;
    B b;
    C() { std::cout << "C()" << std::endl; }
    ~C() { std::cout << "~C()" << std::endl; }
};

int main()
{
    C obj;
}
```

## Капсулация и модификатори за достъп

**Модификатори за достъп:**
| Модификатор | Описание |
|------------|----------|
| private    | Достъп само от класа |
| protected  | Достъп от класа и наследниците |
| public     | Достъп отвън |

```c++
class Student
{
private:
    int age;
    float gpa;
    char* name;

public:
    Student(int age, float gpa, const char* name)
    {
        this->age = age;
        this->gpa = gpa;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    ~Student()
    {
        delete[] name;
    }

    int getAge() const
    {
        return age;
    }

    void setAge(int age)
    {
        this->age = age;
    }
};

int main()
{
    Student student(20, 3.5, "John");
    student.setAge(21);
    int age = student.getAge();
}
```

## Mutable

Спецификаторът mutable позволява член-данна на класа да бъде променяна в константна член-функция.

```c++
class Student
{
private:
    mutable int cachedResult;
    int age;

public:
    Student(int age) : age(age), cachedResult(0) {}

    int getCachedResult() const
    {
        cachedResult++; // Въпреки че getCachedResult е const, cachedResult може да се променя
        return cachedResult;
    }
};

int main()
{
    const Student student(20);
    int result = student.getCachedResult();
}
```