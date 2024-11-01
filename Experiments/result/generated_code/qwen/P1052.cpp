#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

int main() {
    int L, S, T, M;
    scanf("%d %d %d", &L, &S, &M);
    int stones[MAXN] = {0};
    for (int i = 0; i < M; i++) {
        scanf("%d", &stones[i]);
    }

    int dp[L + 1];
    for (int i = 0; i <= L; i++) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;

    for (int i = 0; i <= L; i++) {
        if (dp[i] == INT_MAX) continue;
        for (int j = 0; j < M; j++) {
            if (i + stones[j] > L) break;
            dp[i + stones[j]] = dp[i + stones[j]] < dp[i] + 1 ? dp[i + stones[j]] : dp[i] + 1;
        }
        for (int j = S; j <= T && i + j <= L; j++) {
            dp[i + j] = dp[i + j] < dp[i] + 1 ? dp[i + j] : dp[i] + 1;
        }
    }

    printf("%d\n", dp[L]);
    return 0;
}