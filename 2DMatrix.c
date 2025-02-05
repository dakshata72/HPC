#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrixAdd(double **A, double **B, double **C, int size, int threads) {
    omp_set_num_threads(threads);
    #pragma omp parallel for collapse(2)
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

double** createMatrix(int size) {
    double **matrix = (double**)malloc(size * sizeof(double*));
    for(int i = 0; i < size; i++) {
        matrix[i] = (double*)malloc(size * sizeof(double));
        for(int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100;  // Random values 0-99
        }
    }
    return matrix;
}

void freeMatrix(double **matrix, int size) {
    for(int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {1, 2, 4, 8};
    
    for(int s = 0; s < 5; s++) {
        int size = sizes[s];
        printf("\nMatrix size: %dx%d\n", size, size);
        
        // Create matrices
        double **A = createMatrix(size);
        double **B = createMatrix(size);
        double **C = createMatrix(size);
        
        // Sequential time (1 thread)
        double start = omp_get_wtime();
        matrixAdd(A, B, C, size, 1);
        double seq_time = omp_get_wtime() - start;
        printf("Sequential time: %.4f seconds\n", seq_time);
        
        // Parallel execution with different thread counts
        for(int t = 1; t < 4; t++) {
            start = omp_get_wtime();
            matrixAdd(A, B, C, size, threads[t]);
            double par_time = omp_get_wtime() - start;
            double speedup = seq_time / par_time;
            
            printf("Threads: %d, Time: %.4f seconds, Speedup: %.2fx\n", 
                   threads[t], par_time, speedup);
        }
        
        // Free memory
        freeMatrix(A, size);
        freeMatrix(B, size);
        freeMatrix(C, size);
    }
    
    return 0;
}
