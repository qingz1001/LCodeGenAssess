#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    
    int segments = 1;
    int current_sum = 0;
    
    for (int i = 0; i < N; i++) {
        if (current_sum + A[i] > M) {
            segments++;
            current_sum = A[i];
        } else {
            current_sum += A[i];
        }
    }
    
    printf("%d\n", segments);
    
    return 0;
}