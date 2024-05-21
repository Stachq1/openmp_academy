#include <omp.h>

#include <chrono>
#include <iostream>

int trace(const int* A, unsigned int N) {
  int val = 0;
  for(unsigned int i = 0; i < N; ++i) {
    val += A[i * N + i];
  }
  return val;
}

/*
  Initializes the square matrix A to some values
*/
void init(int* A, unsigned int N) {
  for(unsigned int i = 0; i < N; i++) {
    for(unsigned int j = 0; j < N; j++) {
      A[i * N + j] = i * j;
    }
  }
}

int main() {
  // Set the dimensions of a square matrix
  unsigned int N = 10000;

  // Declare the matrix and initialize its values
  int* A = new int[N * N];
  init(A, N);

  // Compute the trace
  auto trace_start = std::chrono::system_clock::now();
  trace(A, N);
  auto trace_end = std::chrono::system_clock::now();
  double mmul_time = std::chrono::duration_cast<std::chrono::nanoseconds>(trace_end - trace_start).count();

  // Display results
  std::cout << "For square matrix of size: " << N << std::endl;
  std::cout << "Trace computed in: " << mmul_time << "ns" << std::endl;

  // Free memory
  delete[] A;
}