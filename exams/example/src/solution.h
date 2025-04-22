#pragma once

#include <stdexcept>

class calculator {
public:
  int factorial(int n);
  int fibonacci(int n);
  int performed_calculations() const;
};