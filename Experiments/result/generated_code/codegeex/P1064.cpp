#include <stdio.h>
#include <stdlib.h>

#define MAX_N 32000
#define MAX_M 60

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int v[MAX_M + 1], p[MAX_M + 1], q[MAX_M + 1];
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &v[i], &p[i], &q[i]);
    }

    int dp[MAX_N + 1];
    for (int i = 1; i <= n; i++) {
        dp[i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        if (q[i] == 0) { // 主件
            for (int j = n; j >= v[i]; j--) {
                for (int k = 0; k <= 2; k++) {
                    if (j - v[i] >= 0 && v[i + k] != 0) {
                        dp[j] = (dp[j] > dp[j - v[i]] + v[i] * p[i] + (k > 0 ? v[i + k] * p[i + k] : 0)) ? dp[j] : dp[j - v[i]] + v[i] * p[i] + (k > 0 ? v[i + k] * p[i + k] : 0);
                    }
                }
            }
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}