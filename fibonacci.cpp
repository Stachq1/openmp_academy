#include <omp.h>
#include <chrono>
#include <iostream>

unsigned int fibonacci(unsigned int n) {
  if (n <= 1) return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
  // Start the clock
  auto start = std::chrono::system_clock::now();

  // Calculate Fibonacci sequence values for a bunch of numbers ¯\_(ツ)_/¯
  unsigned int a = fibonacci(33);
  unsigned int b = fibonacci(35);
  unsigned int c = fibonacci(37);
  unsigned int d = fibonacci(38);
  unsigned int e = fibonacci(40);
  unsigned int f = fibonacci(42);

  // Stop the clock
  auto end = std::chrono::system_clock::now();
  double time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  // Display results
  std::cout << "fib(33) = " << a << "  fib(35) = " << b << "  fib(37) = " << c << "  fib(38) = " << d << "  fib(40) = " << e << "  fib(42) = " << f << std::endl;
  std::cout << "Solution computed in: " << time << "ms" << std::endl;


}