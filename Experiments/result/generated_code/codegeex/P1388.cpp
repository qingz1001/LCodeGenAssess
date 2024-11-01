#include <stdio.h>

int n, k;
int a[20];
int dp[20][20][20];

int max(int a, int b) {
    return a > b ? a : b;
}

int calc(int l, int r, int m) {
    if (dp[l][r][m] != -1) return dp[l][r][m];
    if (m == 0) return dp[l][r][m] = a[r];
    int res = 0;
    for (int i = l; i < r; i++) {
        for (int j = 0; j < m; j++) {
            res = max(res, calc(l, i, j) * calc(i + 1, r, m - j - 1));
        }
    }
    return dp[l][r][m] = res;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int l = 0; l <= n; l++) {
                dp[i][j][l] = -1;
            }
        }
    }
    printf("%d\n", calc(0, n - 1, k));
    return 0;
}