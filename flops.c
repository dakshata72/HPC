#include <stdio.h>
#include <omp.h>

int main() {
    double start_time, end_time;
    long long int operations = 1000000000; // 1 Billion FLOP
    double a = 1.1, b = 2.2, c;

    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (long long int i = 0; i < operations; i++) {
        c = a * b + c;
    }
    end_time = omp_get_wtime();

    printf("Time taken: %f seconds\n", end_time - start_time);
    printf("Estimated FLOPS: %f GFLOPS\n", operations / (end_time - start_time) / 1e9);
    return 0;
}

