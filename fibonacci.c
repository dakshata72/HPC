#include <stdio.h>
#include <omp.h>

int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int parallel_fibonacci(int n) {
    int x = 0, y = 0;  // Initialize variables
    
    if (n <= 1) return n;
    
    // Specify number of threads and share variables x and y
    #pragma omp parallel shared(x, y) num_threads(2)
    {
        // Show which thread is executing
        #pragma omp single
        {
            printf("Thread %d: Starting parallel computation\n", 
                   omp_get_thread_num());
        }
        
        // Divide work into sections
        #pragma omp sections
        {
            #pragma omp section
            {
                x = fibonacci(n-1);
                printf("Thread %d: Computed fib(n-1) = %d\n", 
                       omp_get_thread_num(), x);
            }
            
            #pragma omp section
            {
                y = fibonacci(n-2);
                printf("Thread %d: Computed fib(n-2) = %d\n", 
                       omp_get_thread_num(), y);
            }
        }
    }
    
    return x + y;
}

int main() {
    int n = 20;
    double start_time, end_time;
    int result;
    
    // Set and print number of threads
    omp_set_num_threads(4);
    
    // Private variable demonstration
    #pragma omp parallel private(result)
    {
        #pragma omp critical
        {
            printf("Thread %d is ready\n", omp_get_thread_num());
        }
    }
    
    printf("\nComputing Fibonacci(%d)...\n", n);
    start_time = omp_get_wtime();
    result = parallel_fibonacci(n);
    end_time = omp_get_wtime();
    
    printf("\nFinal Result: %d\n", result);
    printf("Execution Time: %f seconds\n", end_time - start_time);
    
    return 0;
}
