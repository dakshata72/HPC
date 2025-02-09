#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define BUFFER_SIZE 5  // Maximum buffer size

int buffer[BUFFER_SIZE];  // Shared buffer (array)
int count = 0;           // Number of items in the buffer

void producer() {
    for (int i = 1; i <= 5; i++) {
        #pragma omp critical
        {
            if (count < BUFFER_SIZE) {
                buffer[count] = i;
                printf("Produced: %d by thread %d\n", i, omp_get_thread_num());
                count++;
            }
        }
    }
}

void consumer() {
    for (int i = 1; i <= 5; i++) {
        #pragma omp critical
        {
            if (count > 0) {
                int item = buffer[count - 1];
                count--;
                printf("Consumed: %d by thread %d\n", item, omp_get_thread_num());
            }
        }
    }
}

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        producer();

        #pragma omp section
        consumer();
    }

    return 0;
}

