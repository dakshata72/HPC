#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000  // Default vector size
#define NUM_THREADS 4 // Default number of threads

// Vector Scalar Addition
void vector_scalar_addition(float *vector, float scalar, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        vector[i] += scalar;
    }
}

int main() {
    omp_set_num_threads(NUM_THREADS);

    // Vector Scalar Addition
    float *vector = (float *)malloc(N * sizeof(float));
    for (int i = 0; i < N; i++) vector[i] = i * 1.0f;
    float scalar = 2.5;

    double start_time = omp_get_wtime();
    vector_scalar_addition(vector, scalar, N);
    double end_time = omp_get_wtime();
    printf("Vector Scalar Addition Time: %f seconds\n", end_time - start_time);
    free(vector);

    return 0;
}

