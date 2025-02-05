#include <stdio.h>
#include <omp.h>

int main() {
	int num_threads;
	printf("Enter the number of threads: ");
	scanf("%d", &num_threads);
	
	printf("\nSequential Execution:\n");
	for(int i = 0; i < num_threads; i++){
		printf("Hello , World from thread %d (Sequential)\n", i);
}
	printf("\nParallel Execution:\n");
	#pragma omp parallel num_threads(num_threads)
{	
	int thread_id = omp_get_thread_num();
	   printf("Hello , World from thread %d (parallel)\n", thread_id);

}
return 0;
}


