#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100
#define MAX_E 350
#define MAX_K 100
#define INF 0x3f3f3f3f

int N, E, K;
int X[MAX_N], F[MAX_N], C[MAX_N];
int dp[MAX_E + 1][MAX_K + 1];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d %d", &N, &E, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &X[i], &F[i], &C[i]);
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int x = 1; x <= E; x++) {
        for (int k = 0; k <= K; k++) {
            dp[x][k] = dp[x-1][k] + k;
            
            for (int i = 0; i < N; i++) {
                if (X[i] == x) {
                    for (int buy = 1; buy <= F[i] && buy <= k; buy++) {
                        if (k - buy >= 0) {
                            dp[x][k] = min(dp[x][k], dp[x][k-buy] + buy * C[i]);
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", dp[E][K]);
    return 0;
}