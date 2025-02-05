#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define NUM_THREADS 4 // Default number of threads

// Calculate value of Pi using numerical integration
double calculate_pi(int num_steps) {
    double step = 1.0 / (double)num_steps;
    double sum = 0.0;
    
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    return sum * step;
}

int main() {
    omp_set_num_threads(NUM_THREADS);

    // Pi Calculation
    int num_steps = 100000000;
    double start_time = omp_get_wtime();
    double pi = calculate_pi(num_steps);
    double end_time = omp_get_wtime();
    printf("Calculated Pi: %.10f\n", pi);
    printf("Pi Calculation Time: %f seconds\n", end_time - start_time);

    return 0;
}

