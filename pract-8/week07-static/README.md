# Статични компоненти на клас

Ключовата дума `static` указва, че паметта за даден компонент се заделя **само веднъж** – на ниво **клас**, а не за всеки обект поотделно. Така всички обекти на класа споделят един и същ екземпляр на тази променлива или метод.
- Статичните член-данни **не принадлежат на конкретен обект**, а са общи за целия клас.
- Статичните методи също са достъпни **без да се създава обект от класа**.

*Примери:*
```cpp
class Student {
public:
	static int counter;
	
	Student() {
		++counter;
	}
	
	~Student() {
		--counter;
	}
};

int Student::counter = 0;
```

```cpp
class MathUtils {
public:
    static int square(int x) {
        return x * x;
    }
};

int main() {
	int s = MathUtils::square(5); // Извикване без обект
}
```

***Важно:***
- Статичните методи не могат да достъпват нестатични компоненти!

```cpp
class Example {
    int x = 10;
public:
    static void foo() {
        std::cout << x; // Грешка – x не е статична член-данна
    }
};
```

- **`static` не е част от сигнатурата на функция** – не можете да overload-вате методи, като ги различавате само по `static`

```cpp
class A {
    static void f(int);
    void f(int); // Грешка – конфликт на сигнатури
};
```

---

# `enum`

В C++ `enum` (enumeration) е потребителски дефиниран тип, който се използва за дефиниране на променливи, които могат да приемат само ограничен/краен набор от константни стойности. Това улеснява четимостта и поддръжката на кода, тъй като имената, които дефинирате в `enum` са по-информативни от числовите стойности.

```cpp
enum Color {
	RED,
	GREEN,
	BLUE
};

enum Day : short {
	MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
};
```

В C++11 е въведен `enum class` – по-безопасна алтернатива на обикновените `enum`. Той:
- ограничава имената в собствено пространство (не замърсява глобалното пространство от имена);
- **не позволява неявно преобразуване** към цели числа.
```cpp
enum class LogLevel {
    Info,
    Warning,
    Error
};

void log(LogLevel level, const std::string& message) {
    switch (level) {
        case LogLevel::Info: std::cout << "[INFO] " << message; break;
        case LogLevel::Warning: std::cout << "[WARNING] " << message; break;
        case LogLevel::Error: std::cout << "[ERROR] " << message; break;
    }
}
```
---

# Задача
## Описание

Реализирайте система за управление на потребители. 

---
## Клас **User**

Класът **User** представлява потребител със следните член-данни:
- Уникален идентификатор
- Име
- Възраст
- Уникален email
- Роля (ADMIN, USER)
### Методи:
- `void print()`: Извежда информация за потребителя.
- `bool operator==(const User& other)`: Сравнява по идентификатор.
- `std::ostream& operator<<`: Извежда информация за потребителя в изходен поток (`ostream`).
- `int getUserCount()`: Връща общия брой създадени потребители (чрез статична променлива `userCount`).

---
## Клас **Logger**

Класът **Logger** служи за запис на лог съобщения и следене на броя на логовете в системата.

### Функционалности:

- `void log(LogLevel logLevel, const char* message):` Записва лог съобщение с ниво на важност и текущото време.- [std::time](https://en.cppreference.com/w/cpp/chrono/c/ctime)
- `int getLogCount()`: Връща общия брой на лог съобщенията.
- `static Logger& getInstance()`: Връща единствената инстанция на логера (Singleton).

***Реализирайте Logger чрез Singleton шаблона:***
[Singleton Design Pattern](https://refactoring.guru/design-patterns/singleton)

---
## Клас **UserManager**

Класът **UserManager** управлява колекция от обекти от тип `User`. Той също така автоматично извиква методите на класа `Logger`, за да записва операции. (Ако желаете може да използвате std::vector)
### Функционалности:
- `void addUser(const User& user)`: Добавя нов потребител. Записва лог съобщение.
- `void removeUser(int id)`: Премахва потребител по идентификатор. Записва лог съобщение.
- `void listUsers()`: Извежда списък на всички потребители.
- `User& operator[](int index)`: Достъпва потребител по индекс в списъка.

---
## Юнит тестове

Използвайте Catch2 за тестване на класовете.

---
