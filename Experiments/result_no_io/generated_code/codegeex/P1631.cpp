#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int *A = (int *)malloc(N * sizeof(int));
    int *B = (int *)malloc(N * sizeof(int));
    int *sums = (int *)malloc(N * N * sizeof(int));
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }
    
    int headA = 0, headB = 0;
    for (int i = 0; i < N; i++) {
        sums[i] = A[headA] + B[headB];
        if (A[headA + 1] + B[headB] <= A[headA] + B[headB + 1]) {
            headA++;
        } else {
            headB++;
        }
    }
    
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N - i; j++) {
            if (sums[j] > sums[j + 1]) {
                int temp = sums[j];
                sums[j] = sums[j + 1];
                sums[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        printf("%d ", sums[i]);
    }
    
    free(A);
    free(B);
    free(sums);
    
    return 0;
}