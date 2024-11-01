#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N, A[MAX_N];
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    
    int output_count = (N + 1) / 2;
    
    for (int i = 1; i <= output_count; i++) {
        int current_size = 2 * i - 1;
        int temp[current_size];
        
        for (int j = 0; j < current_size; j++) {
            temp[j] = A[j];
        }
        
        qsort(temp, current_size, sizeof(int), compare);
        
        printf("%d\n", temp[current_size / 2]);
    }
    
    return 0;
}