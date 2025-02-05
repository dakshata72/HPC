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

    // Parallel section with STATIC schedule
    #pragma omp parallel for schedule(static, 10) // Set chunk size to 10
    for (int i = 0; i < SIZE; i++) {
        vector[i] += scalar; // Scalar addition
    }

    double end_time = omp_get_wtime();
    printf("Time taken (STATIC schedule with chunk size 10): %f seconds\n", end_time - start_time);

    return 0;
}

