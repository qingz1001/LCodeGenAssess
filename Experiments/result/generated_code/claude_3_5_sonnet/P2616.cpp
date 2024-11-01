#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100
#define MAX_K 100
#define MAX_E 350
#define INF 0x3f3f3f3f

int K, E, N;
int X[MAX_N], F[MAX_N], C[MAX_N];
int dp[MAX_E + 1][MAX_K + 1];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d %d", &K, &E, &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &X[i], &F[i], &C[i]);
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int i = 1; i <= E; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] = dp[i-1][j] + j;
            
            for (int k = 0; k < N; k++) {
                if (X[k] == i) {
                    for (int l = 0; l <= F[k] && j >= l; l++) {
                        dp[i][j] = min(dp[i][j], dp[i][j-l] + l * C[k]);
                    }
                }
            }
        }
    }

    printf("%d\n", dp[E][K]);
    return 0;
}