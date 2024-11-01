#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_M 100
#define MAX_K 100

int dp[MAX_M + 1][MAX_K + 1];

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int max_per_category[MAX_K + 1];
    for (int i = 1; i <= k; ++i) {
        scanf("%d", &max_per_category[i]);
    }

    int fat[MAX_N + 1], category[MAX_N + 1];
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &fat[i], &category[i]);
    }

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        int f = fat[i];
        int c = category[i];
        if (f > 0 && c >= 1 && c <= k && max_per_category[c] > 0) {
            for (int j = m; j >= f; --j) {
                for (int l = k; l >= c; --l) {
                    dp[j][l] = dp[j][l] > dp[j - f][l - c] + f ? dp[j][l] : dp[j - f][l - c] + f;
                }
            }
        }
    }

    printf("%d\n", dp[m][k]);

    return 0;
}