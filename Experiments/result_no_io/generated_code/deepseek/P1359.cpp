#include <stdio.h>
#include <limits.h>

#define MAXN 200

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n;
    int r[MAXN][MAXN];
    int dp[MAXN];

    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            scanf("%d", &r[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < j; i++) {
            if (r[i][j] != 0) {
                dp[j] = min(dp[j], dp[i] + r[i][j]);
            }
        }
    }

    printf("%d\n", dp[n - 1]);

    return 0;
}