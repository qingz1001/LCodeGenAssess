#include <stdio.h>
#include <stdlib.h>

#define MAXN 55
#define INF 0x3f3f3f3f

int dp[MAXN][MAXN];
int a[MAXN][MAXN];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = -INF;
        }
    }

    dp[1][1] = a[1][1];

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = dp[i-1][j-1] + a[i][j];
            if (j > 1) {
                dp[i][j] = fmax(dp[i][j], dp[i-1][j] + a[i][j]);
            }
        }
    }

    int max_value = -INF;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            max_value = fmax(max_value, dp[i][j]);
        }
    }

    printf("%d\n", max_value);
    return 0;
}