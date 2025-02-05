#include <omp.h>
#include <stdio.h>

#define SIZE 200

int main() {
    int vector[SIZE], scalar = 5;
    for (int i = 0; i < SIZE; i++) {
        vector[i] = i; // Initialize vector
    }

    // Measure time
    double start_time = omp_get_wtime();

    // Parallel section with DYNAMIC schedule
    #pragma omp parallel for schedule(dynamic, 5) // Set chunk size to 5
    for (int i = 0; i < SIZE; i++) {
        vector[i] += scalar; // Scalar addition
    }

    double end_time = omp_get_wtime();
    printf("Time taken (DYNAMIC schedule with chunk size 5): %f seconds\n", end_time - start_time);

    return 0;
}

