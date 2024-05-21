#include <algorithm>
#include <cassert>
#include <cmath>
#include <chrono>
#include <iostream>
#include <limits>

constexpr double pi() { return std::atan(1) * 4; }

void setInitialCondition(double* u0, unsigned int N, double dx) {
  auto f = [](double x) {return 6 * std::sin(pi() * x);};
  for(unsigned int i = 0; i < N; ++i) {
    u0[i] = f(dx * i);
  }
}

void step(double* u_new, double* u_old, unsigned int meshSize, double dx, double dt, double alpha) {
  double dx_sq_inv = 1 / (dx * dx);
  for(unsigned int i = 1; i < meshSize - 1; ++i) {
    u_new[i] = u_old[i] + alpha * dt * dx_sq_inv * (u_old[i + 1] - 2 * u_old[i] + u_old[i - 1]);
  }
}

void minMaxDiff(double* u, unsigned int meshSize) {
  double val_max = std::numeric_limits<double>::min();
  double val_min = std::numeric_limits<double>::max();
  for(unsigned int i = 0; i < meshSize; ++i) {
    val_max = std::max(val_max, u[i]);
    val_min = std::min(val_min, u[i]);
  }
  std::cout << "The difference between max and min is: " << val_max - val_min << std::endl;
}

// Stability condition check
void checkStability(double alpha, double dx, double dt) {
    double r = alpha * dt / (dx * dx);
    std::cout << "r: " << r << std::endl;
    assert(r < 0.5 && "This scheme is only stable if r < 0.5.");
}

int main() {
  const unsigned int meshSize = 100;
  const unsigned int numSteps = 10000;

  const double dx = 1.0 / (meshSize - 1);
  const double dt = 0.0001;
  const double alpha = 0.1;

  checkStability(alpha, dx, dt);

  double* u_old = new double[meshSize];
  double* u_new = new double[meshSize];

  setInitialCondition(u_old, meshSize, dx);
  setInitialCondition(u_new, meshSize, dx);

  // Start the clock
  auto start = std::chrono::system_clock::now();

  // Iterate over steps to find the solution
  for(unsigned int i = 0; i < numSteps; ++i) {
    step(u_new, u_old, meshSize, dx, dt, alpha);
    std::copy(u_new, u_new + meshSize, u_old);
    // Compute the difference between max and min value at each iteration
    minMaxDiff(u_new, meshSize);
  }

  // Stop the clock
  auto end = std::chrono::system_clock::now();
  double time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  // Display results
  std::cout << "For mesh size of: " << meshSize << std::endl;
  std::cout << "Solution computed in: " << time << "ms" << std::endl;
}