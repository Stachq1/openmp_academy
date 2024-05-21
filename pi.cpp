#include <chrono>
#include <iostream>

// Function which we are integrating
double f(double x) {
  return 4 / (1 + x * x);
}

int main() {
  // Define mesh size and integration step
  unsigned int meshSize = 1000000;
  double dx = 1.0 / meshSize;

  // Start the clock
  auto pi_start = std::chrono::system_clock::now();

  // Compute pi
  double sum = 0.0;
  for(unsigned int i = 0; i <= meshSize; ++i) {
    double x = i * dx;
    sum += f(x);
  }

  double pi = sum * dx;

  // Stop the clock
  auto pi_end = std::chrono::system_clock::now();
  double pi_time = std::chrono::duration_cast<std::chrono::milliseconds>(pi_end - pi_start).count();

  // Display results
  std::cout << "For mesh size of: " << meshSize << std::endl;
  std::cout << "Pi computed in: " << pi_time << "ms" << std::endl;
  std::cout << "With value: " << pi << std::endl;

}