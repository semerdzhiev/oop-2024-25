# Файлове и потоци

![Йерархията на потоците в C++](https://iq.opengenus.org/content/images/2022/12/pic1-1.png)

**ПОТОК** - Редица от байтове, които се движат в една посока. Потокът може да бъде **входен** или **изходен**.
Пример за входен поток - `cin`
Пример за изходен поток - `cout`
## Декларация на файл
- за четене
  `std::ifstream iFileName` 
- за вмъкване
  `std::ofstream oFileName`
- за извличане и вмъкване
  `std::fstream ioFileName`

## Видове файлове
- Текстови файлвое
- Двочини файлове
## Режим на достъп

| Member Constant | Stands For     | Access                                                                                   |
| --------------- | -------------- | ---------------------------------------------------------------------------------------- |
| ios::in         | input          | File open for reading: the internal stream buffer supports input operations.             |
| ios::out        | output         | File open for writing: the internal stream buffer supports output operations.            |
| ios::binary     | binary         | Operations are performed in binary mode rather than text.                                |
| ios::ate        | at end         | The output position starts at the end of the file.                                       |
| ios::app        | append         | All output operations happen at the end of the file, appending to its existing contents. |
| ios::trunc      | truncate       | Any contents that existed in the file before it is open are discarded.                   |
| ios::nocreate   | Do not create  | Does not allow to create new file if it does not exist.                                  |
| ios::noreplace  | Do not replace | Does not replace old file with new file.                                                 |
## Таблица с методите на входно-изходните потоци:

| Член-функция/Оператор                                             | Описание                                                                                                      |
| ----------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------- |
| `istream& operator>>(T& value)`                                   | Оператор за извличане (вход) на данни от поток в променлива `value`.                                          |
| `ostream& operator<<(const T& value)`                             | Оператор за запис (изход) на данни от променлива `value` в поток.                                             |
| `istream& get(char& c)`                                           | Чете един символ от входния поток и го записва в променливата `c`.                                            |
| `istream& get(char* buffer, streamsize n)`                        | Чете до `n` символа в `buffer` от входния поток, като спира при нов ред или достигане на `n`.                 |
| `ostream& put(char c)`                                            | Записва един символ в изходния поток.                                                                         |
| `istream& read(char* buffer, streamsize n)`                       | Чете точно `n` байта в `buffer` от входния поток.                                                             |
| `ostream& write(const char* buffer, streamsize n)`                | Записва точно `n` байта от `buffer` в изходния поток.                                                         |
| `istream& ignore(streamsize n = 1, int delim = EOF)`              | Игнорира `n` символа или до среща на `delim` от входния поток.                                                |
| `istream& getline(char* buffer, streamsize n, char delim = '\n')` | Чете символи от входния поток и ги записва в `buffer`, докато не срещне `delim` или достигне `n` символа.     |
| `istream& peek()`                                                 | Връща следващия символ от входния поток без да го премахва.                                                   |
| **Позиция в поток:**                                              |                                                                                                               |
| `istream& seekg(streamoff p, ios::seekdir r)`                     | Премества указателя за четене в потока с `p` байта спрямо позицията `r` (`ios::beg`, `ios::cur`, `ios::end`). |
| `ostream& seekp(streamoff p, ios::seekdir r)`                     | Премества указателя за запис в потока с `p` байта спрямо позицията `r` (`ios::beg`, `ios::cur`, `ios::end`).  |
| `streampos tellg()`                                               | Връща текущата позиция на указателя за четене в потока.                                                       |
| `streampos tellp()`                                               | Връща текущата позиция на указателя за запис в потока.                                                        |
| **Състояние на поток: **                                          |                                                                                                               |
| `bad()`                                                           | Връща `true`, ако е възникнала фатална грешка при потока.                                                     |
| `fail()`                                                          | Връща `true`, ако е възникнала грешка при операциите с потока (например, невалиден формат).                   |
| `eof()`                                                           | Връща `true`, ако потокът е достигнал края на файла при четене.                                               |
| `good()`                                                          | Връща `true`, ако потока е в добро състояние (без грешки или достигнат край на файл).                         |
| `clear()`                                                         | Изчиства флаговете на потока и го връща в добро състояние.                                                    |
| `flush()`                                                         | Изпразва буфера на изходния поток, като записва всички данни.                                                 |

*Малко примери:*

*Четене от файл*
```cpp

#include <iostream>
#include <fstream>  // Необходим за работа с файлове

int main() {

    std::ofstream outFile("example.txt");  // Файлът ще бъде създаден, ако не съществува

    if (!outFile) {  // Проверка дали файлът е отворен успешно
        std::cerr << "Cannot open file!" << std::endl;
        return 1;
    }

    // Записване на текст в файла
    outFile << "Hello world!" << std::endl;
    outFile << "An example for writing in a file" << std::endl;

    // Затваряне на файла
    outFile.close();

    return 0;
}

```

*Писане във файл*
```cpp
#include <iostream>
#include <fstream>  // Необходим за работа с файлове
#include <string>   // За работа с низове

using namespace std;

int main() {

    std::ifstream inFile("example.txt");  // Отваряне на съществуващ! текстов файл

    if (!inFile) {  // Проверка дали файлът е отворен успешно
        std::cerr << "Не може да се отвори файлът!" << std::endl;
        return 1;
    }

    std::string line;
    
    // Четене на съдържанието на файла ред по ред
    while (getline(inFile, line)) {
        std::cout << line << std::endl;  // Извеждане на реда на екрана
    }

    // Затваряне на файла
    inFile.close();

    return 0;
}

```

*Двочни файлове:*
```cpp
#include <iostream>
#include <fstream>

int main() {
    const int size = 5;
    int numbers[size] = {10, 20, 30, 40, 50};  // Масив от числа за запис
    int readNumbers[size];                    // Масив за четене от файл

    // 1. Записване на масива в двоичен файл
    std::ofstream outFile("binary_data.bin", std::ios::binary | std::ios::out); // Отваряне в двоичен режим
    if (!outFile) {
        std::cerr << "Cannot open file!" << std::endl;
        return 1;
    }

    // Записване на целия масив
    outFile.write(reinterpret_cast<char*>(numbers), sizeof(numbers));

    // Проверка за успешно записване
    if (!outFile) {
        std::cerr << "Error!" << std::endl;
        return 1;
    }

    outFile.close();

    // 2. Четене на масива от двоичния файл
    std::ifstream inFile("binary_data.bin", std::ios::binary | std::ios::in); // Отваряне в двоичен режим
    if (!inFile) {
        std::cerr << "Cannot open file!" << std::endl;
        return 1;
    }

    // Четене на целия масив
    inFile.read(reinterpret_cast<char*>(readNumbers), sizeof(readNumbers));

    // Проверка за успешно четене
    if (!inFile) {
        std::cerr << "Error!" << std::endl;
        return 1;
    }

    inFile.close();

    // 3. Извеждане на прочетените данни
    std::cout << "Data: ";
    for (int i = 0; i < size; ++i) {
        std::cout << readNumbers[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

```

---

# Класове и файлове 

Конкретни примери може да намерите в директорията *snippets*

---

# Resource acquisition is initialization (RAII)

**RAII** е концепция, при която **ресурсите се придобиват по време на инициализацията на обекта** и се освобождават автоматично, когато обектът излиза от обхвата си (достигне до края на scope-a) (при унищожаване на обекта). Това означава, че ресурсите са свързани с продължителността на живота на обекта, и когато обектът бъде унищожен (например излиза от обхвата), ресурсите се освобождават автоматично.

*Пример:*

```cpp
#include <iostream>
#include <fstream>

class FileWrapper {
private:
    std::ifstream file;
public:
    FileWrapper(const std::string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file");
        }
    }

    ~FileWrapper() {
        if (file.is_open()) {
            file.close();
        }
    }

    void read() {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
    }
};

int main() {
    try {
        FileWrapper file("example.txt");
        file.read();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    // Файлът ще бъде автоматично затворен при излизане от обхвата на file
    return 0;
}

```

# Задача

Създайте клас **Library**, който управлява колекция от книги, представени чрез клас Book. Всяка книга има заглавие, автор, жанр, брой страници и година на издаване. За удобство може да използвате класа Vector, който реализирахме миналата седмица.  Ако е нужното имплементирайте деструктор, копиращ конструктор и оператор за присвояване.

---

Класът **Book** трябва да поддържа следните функционалности:
- `print()`: Извежда информацията за книгата.
- `operator==(const Book& other)`: Сравнява две книги по заглавие, автор и година.
- `operator<(const Book& other)`: Сравнява книгите по година на издаване.
- `operator<<`: Отпечатва информацията за книгата в поток.

Класът **Library** трябва да поддържа следните функционалности:
- `addBook(const Book& b)`: Добавя нова книга в библиотеката.
- `removeBook(const Book& b)`: Премахва книга от библиотеката.
- `findBookByTitle(const char* title)`: Търси книга по заглавие и връща нейното копие.
- `listBooks()`: Извежда всички книги в библиотеката.
- `saveToFile(const char* filename)`: Запазва библиотеката във файл.
- `loadFromFile(const char* filename)`: Зарежда библиотека от файл.
- `operator[](int index)`: Достъпва книга по индекс.
- `operator+ (const Library& other)`: Обединява две библиотеки.
- `operator== (const Library& other)`: Проверява дали две библиотеки съдържат едни и същи книги.
- `operator<<`: Отпечатва информацията за библиотеката в поток.

### Юнит тестове
Напишете юнит тестове, които покриват поне 50% от методите.