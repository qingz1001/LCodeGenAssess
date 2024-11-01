#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int *S = (int *)malloc(N * sizeof(int));
    int *A = (int *)malloc(N * sizeof(int));
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    
    long long *prefix_sum_A = (long long *)malloc((N + 1) * sizeof(long long));
    prefix_sum_A[0] = 0;
    
    for (int i = 1; i <= N; i++) {
        prefix_sum_A[i] = prefix_sum_A[i - 1] + A[i - 1];
    }
    
    for (int X = 1; X <= N; X++) {
        long long max_tiredness = 0;
        
        for (int i = X - 1; i >= 0; i--) {
            long long current_tiredness = 2 * (S[X - 1] - S[i]) + prefix_sum_A[X] - prefix_sum_A[i + 1];
            if (current_tiredness > max_tiredness) {
                max_tiredness = current_tiredness;
            }
        }
        
        printf("%lld\n", max_tiredness);
    }
    
    free(S);
    free(A);
    free(prefix_sum_A);
    
    return 0;
}