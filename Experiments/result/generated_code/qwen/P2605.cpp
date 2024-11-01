#include <stdio.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    
    int D[N], C[N], S[N], W[N];
    for (int i = 1; i < N; i++) {
        scanf("%d", &D[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &C[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &S[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &W[i]);
    }

    int dp[K + 1][N + 1];
    for (int i = 0; i <= K; i++) {
        for (int j = 0; j <= N; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    for (int k = 1; k <= K; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < i; j++) {
                if (D[i] - D[j] <= S[j]) {
                    dp[k][i] = fmin(dp[k][i], dp[k - 1][j] + C[i]);
                } else {
                    dp[k][i] = fmin(dp[k][i], dp[k - 1][j] + C[i] + W[i]);
                }
            }
        }
    }

    printf("%d\n", dp[K][N]);

    return 0;
}