#include <stdio.h>
#include <limits.h>

int main() {
    int N, S;
    scanf("%d %d", &N, &S);
    
    int C[N], Y[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &C[i], &Y[i]);
    }
    
    long long min_cost = 0;
    int min_C = INT_MAX;
    
    for (int i = 0; i < N; i++) {
        if (C[i] < min_C) {
            min_C = C[i];
        }
        min_cost += (long long)min_C * Y[i];
        min_C += S;
    }
    
    printf("%lld\n", min_cost);
    
    return 0;
}