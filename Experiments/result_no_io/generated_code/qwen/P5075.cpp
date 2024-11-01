#include <stdio.h>

#define MOD 255

int main() {
    int M, P;
    scanf("%d %d", &M, &P);
    
    int A;
    scanf("%d", &A);
    
    int O, S, U;
    scanf("%d %d %d", &O, &S, &U);
    
    long long dp[M + 1][A + 1];
    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= A; j++) {
            dp[i][j] = 0;
        }
    }
    
    dp[0][0] = 1;
    
    for (int i = 1; i <= M; i++) {
        for (int j = 0; j <= A; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= 1) {
                dp[i][j] += dp[i - 1][j - 1] * (O * j * j + S * j + U);
                dp[i][j] %= MOD;
            }
        }
    }
    
    printf("%lld\n", dp[M][A]);
    
    return 0;
}