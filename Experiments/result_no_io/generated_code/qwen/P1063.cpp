#include <stdio.h>
#include <stdlib.h>

#define MAXN 105

int main() {
    int N;
    scanf("%d", &N);
    int head[MAXN], tail[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &head[i], &tail[(i + 1) % N]);
    }

    long long dp[MAXN][MAXN];
    for (int len = 2; len <= N; len++) {
        for (int i = 0; i <= N - len; i++) {
            int j = (i + len) % N;
            dp[i][j] = 0;
            for (int k = i; k < j; k++) {
                dp[i][j] = fmax(dp[i][j], dp[i][k] + dp[k][j] + (long long)head[i] * tail[k] * tail[j]);
            }
        }
    }

    printf("%lld\n", dp[0][(N - 1 + N) % N]);

    return 0;
}