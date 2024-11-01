#include <stdio.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    
    int D[N];
    for (int i = 1; i < N; ++i) {
        scanf("%d", &D[i]);
    }
    
    int C[N], S[N], W[N];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &C[i]);
    }
    for (int i = 0; i < N; ++i) {
        scanf("%d", &S[i]);
    }
    for (int i = 0; i < N; ++i) {
        scanf("%d", &W[i]);
    }
    
    int dp[K + 1][N + 1];
    for (int i = 0; i <= K; ++i) {
        for (int j = 0; j <= N; ++j) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    
    for (int k = 1; k <= K; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = i; j >= 0; --j) {
                if (dp[k - 1][j] != INF) {
                    int cost = dp[k - 1][j];
                    if (i == j) {
                        cost += C[i];
                    } else {
                        int range = S[j];
                        int pos = j;
                        while (pos < N && D[pos + 1] - D[j] <= range) {
                            ++pos;
                        }
                        cost += C[i] + W[j];
                        dp[k][i] = fmin(dp[k][i], cost);
                    }
                }
            }
        }
    }
    
    int ans = INF;
    for (int i = 0; i <= N; ++i) {
        ans = fmin(ans, dp[K][i]);
    }
    
    printf("%d\n", ans);
    
    return 0;
}