#include <stdio.h>
#include <omp.h>

#define MAX_SIZE 1000

void sort(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        #pragma omp parallel for
        for(int j = 0; j < n-1-i; j++) {
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int n, arr1[MAX_SIZE], arr2[MAX_SIZE];
    long long result = 0;
    
    // Input size
    printf("Enter size of vectors: ");
    scanf("%d", &n);
    
    // Input first vector
    printf("Enter elements of first vector:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr1[i]);
    
    // Input second vector
    printf("Enter elements of second vector:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr2[i]);
    
    // Sort first array in ascending order
    sort(arr1, n);
    
    // Sort second array in descending order
    sort(arr2, n);
    for(int i = 0; i < n/2; i++) {
        int temp = arr2[i];
        arr2[i] = arr2[n-1-i];
        arr2[n-1-i] = temp;
    }
    
    // Calculate minimum scalar product in parallel
    #pragma omp parallel for reduction(+:result)
    for(int i = 0; i < n; i++) {
        result += (long long)arr1[i] * arr2[i];
    }
    
    printf("Minimum scalar product: %lld\n", result);
    return 0;
}
