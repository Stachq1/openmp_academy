#include <omp.h>

#include <chrono>
#include <iostream>
#include <algorithm>
#include <limits.h>

int max(const int* A, unsigned int N) {
  int val = INT_MIN;
  for(unsigned int i = 0; i < N; ++i) {
    val = std::max(val, A[i]);
  }
  return val;
}

/*
  Initializes the vector A to some values
*/
void init(int* A, unsigned int N) {
  for(unsigned int i = 0; i < N; i++) {
    A[i] = i;
  }
}

int main() {
  // Set the dimension of the vector
  unsigned int N = 100000000;

  // Declare the vector and initialize its values
  int* A = new int[N];
  init(A, N);

  // Compute the max element
  auto max_start = std::chrono::system_clock::now();
  max(A, N);
  auto max_end = std::chrono::system_clock::now();
  double max_time = std::chrono::duration_cast<std::chrono::milliseconds>(max_end - max_start).count();

  // Display results
  std::cout << "For vector of size: " << N << std::endl;
  std::cout << "Maximum computed in: " << max_time << "ms" << std::endl;

  // Free memory
  delete[] A;
}