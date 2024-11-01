#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N;
    int A[MAX_N];
    
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    
    for (int i = 1; i <= N; i += 2) {
        int temp[i];
        for (int j = 0; j < i; j++) {
            temp[j] = A[j];
        }
        
        qsort(temp, i, sizeof(int), cmp);
        
        printf("%d\n", temp[i / 2]);
    }
    
    return 0;
}