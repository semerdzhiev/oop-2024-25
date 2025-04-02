# Изключения

![Exception hierarchy](https://www.tutorialspoint.com/cplusplus/images/cpp_exceptions.jpg)

- Изключения се предизвикват от невалидни състояния, до които програмата може да достигне в хода на нейното изпълнение

## try-catch

### try

- Дефинира блок от код, който може да предизвика изключение

### catch

- Дефинира блок, който се изпълнява само когато дадено изключение е прихванато

### Пример

```c++
#include <iostream>
#include <exception>

bool trianglePerimeter(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw std::invalid_argument("The sides of the triangle have to be positive!");
    }

    if(a + b <= c || a + c <= b || b + c <= a) {
        throw std::invalid_argument("This is not a triangle!");
    }

    return a + b + c;
}

int main() {
    double a, b, c;
    std::cin >> a >> b >> c;

    try {
        double perimeter = trianglePerimeter(a, b, c);
        std::cout << "The perimeter is: " << perimeter << std::endl;
    } catch (std::invalid_argument& ex) {
        std::cout << ex.what() << std::endl;
    }
}
```

## Задачи

### Задача 1

Създайте клас Board, който представлява матрица от цели числа n x m, която се запълва последователно (от ляво надясно по редове).

Board трябва да поддържа следните операции:
- insert(int num) - добавя подаденото число в матрицата
- insertAt(size_t i, size_t j, int num) - добавя подаденото число на позиция (i,j), като тази позиция трябва да е в рамките на запълнената част на матрицата и трябва всички елементи (включително текущият на (i, j)) да бъдат изместени с една позиция напред.
- removeAt(size_t i, size_t j) - премахва елементът на позиция (i, j). Ако тя не е последната, то трябва елементите след нея да бъдат изместени с една позиция назад.
- last() - връща елементът на последната позиция в матрицата
- at(size_t i, size_t j) - връща елементът на позиция (i, j) в матрицата
- update(size_t i, size_t j, int num) - променя числото на позиция (i, j) в матрицата на num
- print() - извежда съдържанието на матрицата на стандартния изход, като за незапълнените позиции се използва '*'.

За невалидно подадени индекси с помощта на изключения да се изведе подходяща грешка на стандартния изход.