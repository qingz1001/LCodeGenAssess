#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

int main() {
    int n;
    scanf("%d", &n);
    int L[MAXN], R[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &L[i], &R[i]);
    }

    int dp[MAXN][MAXN];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = INT_MAX / 2;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (dp[j][i - j] != INT_MAX / 2) {
                dp[j][i - j] += abs(L[i - 1] - L[j]) + abs(R[i - 1] - R[j]);
            }
            if (dp[i - j][j] != INT_MAX / 2) {
                dp[i - j][j] += abs(L[i - 1] - R[j]) + abs(R[i - 1] - L[j]);
            }
        }
    }

    int min_cost = INT_MAX / 2;
    for (int i = 0; i <= n; ++i) {
        min_cost = dp[i][n - i] < min_cost ? dp[i][n - i] : min_cost;
    }

    printf("%d\n", min_cost);

    return 0;
}