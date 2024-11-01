#include <stdio.h>

#define MAX_N 100
#define MAX_T 1000

int main() {
    int N, T;
    scanf("%d %d", &N, &T);
    
    double value[MAX_N];
    for (int i = 0; i < N; i++) {
        int m, v;
        scanf("%d %d", &m, &v);
        value[i] = (double)v / m;
    }
    
    double dp[MAX_T + 1];
    for (int i = 0; i <= T; i++) {
        dp[i] = 0.0;
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = T; j >= 0; j--) {
            if (j >= value[i]) {
                dp[j] = fmax(dp[j], dp[j - value[i]] + value[i]);
            }
        }
    }
    
    printf("%.2f\n", dp[T]);
    
    return 0;
}