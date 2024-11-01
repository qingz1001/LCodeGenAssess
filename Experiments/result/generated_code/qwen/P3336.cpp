#include <stdio.h>
#include <stdlib.h>

#define MOD 19940417

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    
    if (K == 0) {
        printf("1 1\n");
        return 0;
    }
    
    int x[K], y[K];
    for (int i = 0; i < K; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    
    // Sort by x-coordinate
    for (int i = 0; i < K - 1; i++) {
        for (int j = i + 1; j < K; j++) {
            if (x[i] > x[j]) {
                int tempX = x[i];
                int tempY = y[i];
                x[i] = x[j];
                y[i] = y[j];
                x[j] = tempX;
                y[j] = tempY;
            }
        }
    }
    
    long long count = 1;
    long long max_value = 0;
    
    for (int i = 0; i < K - 1; i++) {
        int dx = abs(x[i + 1] - x[i]);
        int dy = abs(y[i + 1] - y[i]);
        
        if (dx != dy) {
            count = (count * 2) % MOD;
        }
        
        max_value = (max_value + (long long)dy) % MOD;
    }
    
    printf("%lld %lld\n", count, max_value);
    
    return 0;
}