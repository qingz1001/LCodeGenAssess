#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 0x3f3f3f3f

int n, p, S;
int W[MAXN], V[MAXN];
int dp[MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &p, &S);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &W[i], &V[i]);
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= S; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = dp[i - 1][j];
                if (j >= W[i]) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - W[i]] + V[i]);
                }
            }
        }
    }

    int ans = INF;
    for (int w = 1; w <= S; w++) {
        if (dp[n][w] >= p) {
            ans = min(ans, w);
        }
    }

    if (ans == INF) {
        printf("No Solution!\n");
    } else {
        printf("%d\n", ans);
    }

    return 0;
}