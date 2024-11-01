#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 2000001

long long dp[MAX_N];
int w[MAX_N];

long long min(long long a, long long b) {
    return a < b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i <= n; i++) {
        scanf("%d", &w[i]);
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i * MAX_N + j] = LLONG_MAX;
            for (int k = i; k < j; k++) {
                dp[i * MAX_N + j] = min(dp[i * MAX_N + j], 
                                        dp[i * MAX_N + k] + dp[(k+1) * MAX_N + j] + 
                                        1LL * w[i-1] * w[k] * w[j]);
            }
        }
    }

    printf("%lld\n", dp[1 * MAX_N + n]);

    return 0;
}