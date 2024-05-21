#include <omp.h>

#include <chrono>
#include <iostream>

/*
  Performs multiplication of two square matrices A and B
  C = A * B
*/
void mmul(int* C, const int* A, const int* B, unsigned int N) {
  #pragma omp parallel for collapse(2)
  for(unsigned int i = 0; i < N; i++) {
    for(unsigned int j = 0; j < N; j++) {
      for(unsigned int k = 0; k < N; k++) {
        C[i * N + j] += A[i * N + k] * B[k * N + j];
      }
    }
  }
}

/*
  Initializes the square matrices A and B to some values and C to zero matrix
*/
void minit(int* C, int* A, int* B, unsigned int N) {
  #pragma omp parallel for collapse(2)
  for(unsigned int i = 0; i < N; i++) {
    for(unsigned int j = 0; j < N; j++) {
      C[i * N + j] = 0;
      A[i * N + j] = 1;
      B[i * N + j] = 1;
    }
  }
}

int main() {
  // Set the size of the square matrices
  unsigned int N = 2000;

  // Declare matrices
  int* A = new int[N * N];
  int* B = new int[N * N];
  int* C = new int[N * N];

  // Initialize their values
  auto minit_start = std::chrono::system_clock::now();
  minit(C, A, B, N);
  auto minit_end = std::chrono::system_clock::now();
  double minit_time = std::chrono::duration_cast<std::chrono::milliseconds>(minit_end - minit_start).count();

  // Perform multiplication
  auto mmul_start = std::chrono::system_clock::now();
  mmul(C, A, B, N);
  auto mmul_end = std::chrono::system_clock::now();
  double mmul_time = std::chrono::duration_cast<std::chrono::milliseconds>(mmul_end - mmul_start).count();

  // Display results
  std::cout << "For square matrix of size: " << N << std::endl;
  std::cout << "Initialization: " << minit_time << "ms" << std::endl;
  std::cout << "Multiplication: " << mmul_time << "ms" << std::endl;

  // Free memory
  delete[] A;
  delete[] B;
  delete[] C;
}