#include <stdio.h>
#include <string.h>

#define MAX_N 1000005

long long dp[2][MAX_N];

long long mod(long long x, long long P) {
    return (x % P + P) % P;
}

int main() {
    long long N, K, M, P;
    scanf("%lld %lld %lld %lld", &N, &K, &M, &P);

    memset(dp, 0, sizeof(dp));
    
    int curr = 0, prev = 1;
    for (int i = 1; i <= N; i++) {
        dp[curr][i] = 1;
    }

    for (int k = 2; k <= K; k++) {
        long long sum = 0;
        curr ^= 1;
        prev ^= 1;
        
        memset(dp[curr], 0, sizeof(dp[curr]));

        for (int i = 1; i <= N; i++) {
            sum = mod(sum + dp[prev][i-1], P);
            if (i > M) {
                sum = mod(sum - dp[prev][i-M-1], P);
            }
            dp[curr][i] = sum;
        }
    }

    long long result = 0;
    for (int i = 1; i <= N; i++) {
        result = mod(result + dp[curr][i], P);
    }

    printf("%lld\n", result);

    return 0;
}