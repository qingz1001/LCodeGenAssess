#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

long long calculateMaxBase(int N) {
    long long *dp = (long long *)malloc((N + 1) * sizeof(long long));
    int i, j;
    
    for (i = 0; i <= N; i++) {
        dp[i] = i;
    }
    
    for (i = 1; i < N; i++) {
        for (j = N; j > i; j--) {
            dp[j] = (dp[j] + dp[j-1]) % MOD;
        }
    }
    
    long long maxBase = dp[N];
    free(dp);
    return maxBase;
}

int main() {
    int N;
    scanf("%d", &N);
    
    long long result = calculateMaxBase(N);
    printf("%lld\n", result);
    
    return 0;
}