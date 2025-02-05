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

    #pragma omp parallel
    {
        // Parallel for loop with DYNAMIC schedule and NOWAIT clause
        #pragma omp for schedule(dynamic, 5) nowait
        for (int i = 0; i < SIZE; i++) {
            vector[i] += scalar; // Scalar addition
        }
    }

    double end_time = omp_get_wtime();
    printf("Time taken (DYNAMIC schedule with chunk size 5 and NOWAIT): %f seconds\n", end_time - start_time);

    return 0;
}

