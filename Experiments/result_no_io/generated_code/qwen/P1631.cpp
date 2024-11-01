#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N;
    scanf("%d", &N);
    
    int A[N], B[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }
    
    long long sums[N*N];
    int k = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sums[k++] = (long long)A[i] + B[j];
        }
    }
    
    qsort(sums, N*N, sizeof(long long), compare);
    
    for (int i = 0; i < N; i++) {
        printf("%lld ", sums[i]);
    }
    printf("\n");
    
    return 0;
}