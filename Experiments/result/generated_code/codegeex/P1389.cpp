#include <stdio.h>
#include <stdlib.h>

#define MAXN 150
#define INF 0x3f3f3f3f

int N;
int V[MAXN + 1], A[MAXN + 1];
int dp[MAXN + 1][MAXN + 1][2];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &V[i]);
    for (int i = 1; i <= N; i++)
        scanf("%d", &A[i]);

    for (int len = 1; len <= N; len++) {
        for (int l = 1; l <= N - len + 1; l++) {
            int r = l + len - 1;
            dp[l][r][0] = dp[l][r][1] = -INF;

            if (len == 1) {
                dp[l][r][0] = 0;
                dp[l][r][1] = V[1];
            } else {
                for (int k = l; k < r; k++) {
                    if (A[k] + 1 == A[r] && A[l] - 1 == A[k]) {
                        dp[l][r][0] = dp[l][r][0] > dp[l][k][0] + dp[k + 1][r][0] ? dp[l][r][0] : dp[l][k][0] + dp[k + 1][r][0];
                        dp[l][r][1] = dp[l][r][1] > dp[l][k][0] + dp[k + 1][r][1] + V[len] ? dp[l][r][1] : dp[l][k][0] + dp[k + 1][r][1] + V[len];
                    }
                    if (A[k] + 1 == A[l] && A[r] - 1 == A[k]) {
                        dp[l][r][0] = dp[l][r][0] > dp[l][k][1] + dp[k + 1][r][0] ? dp[l][r][0] : dp[l][k][1] + dp[k + 1][r][0];
                        dp[l][r][1] = dp[l][r][1] > dp[l][k][1] + dp[k + 1][r][1] + V[len] ? dp[l][r][1] : dp[l][k][1] + dp[k + 1][r][1] + V[len];
                    }
                }
                if (A[l] + 1 == A[r]) {
                    dp[l][r][0] = dp[l][r][0] > dp[l + 1][r - 1][0] ? dp[l][r][0] : dp[l + 1][r - 1][0];
                    dp[l][r][1] = dp[l][r][1] > dp[l + 1][r - 1][0] + V[len] ? dp[l][r][1] : dp[l + 1][r - 1][0] + V[len];
                }
            }
        }
    }

    printf("%d\n", dp[1][N][1]);
    return 0;
}