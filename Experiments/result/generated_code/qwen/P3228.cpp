#include <stdio.h>

int main() {
    long long N, K, M, P;
    scanf("%lld %lld %lld %lld", &N, &K, &M, &P);

    // Initialize the DP array
    long long dp[K + 1][N + 1];
    for (long long i = 0; i <= K; ++i) {
        for (long long j = 0; j <= N; ++j) {
            dp[i][j] = 0;
        }
    }

    // Base case: There's one way to have a price of 0 on day 0
    dp[0][0] = 1;

    // Fill the DP table
    for (long long k = 1; k <= K; ++k) {
        for (long long n = 1; n <= N; ++n) {
            dp[k][n] = dp[k - 1][n - 1];
            if (n > M) {
                dp[k][n] = (dp[k][n] + dp[k - 1][n - M - 1]) % P;
            }
        }
    }

    // The answer is the number of ways to have a price between 1 and N on day K
    long long result = 0;
    for (long long n = 1; n <= N; ++n) {
        result = (result + dp[K][n]) % P;
    }

    printf("%lld\n", result);
    return 0;
}