#include <iostream>
#include <omp.h>

int main() {
  // Check how many threads OpenMP will spawn
  int max_id = omp_get_max_threads();
  std::cout << "Max number of threads available: " << max_id << std::endl;

  // Start a parallel region and let each thread greet you
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    std::cout << "Hello from thread: " << id << std::endl;
  }
}
