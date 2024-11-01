#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 20005
#define MAXK 105

int N, K;
int D[MAXN], C[MAXN], S[MAXN], W[MAXN];
int dp[MAXK][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 2; i <= N; i++) {
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

    // Initialize dp array
    for (int i = 0; i <= K; i++) {
        for (int j = 0; j <= N; j++) {
            dp[i][j] = INT_MAX;
        }
    }
    dp[0][0] = 0;

    // Fill dp array
    for (int i = 1; i <= K; i++) {
        for (int j = 1; j <= N; j++) {
            int cost = 0;
            for (int k = j - 1; k >= 0; k--) {
                if (D[j] - D[k + 1] <= S[j]) {
                    cost += W[k + 1];
                }
                if (dp[i - 1][k] != INT_MAX) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + C[j] + cost);
                }
            }
        }
    }

    // Find the minimum cost
    int min_cost = INT_MAX;
    for (int i = 1; i <= K; i++) {
        for (int j = 1; j <= N; j++) {
            min_cost = min(min_cost, dp[i][j]);
        }
    }

    printf("%d\n", min_cost);
    return 0;
}