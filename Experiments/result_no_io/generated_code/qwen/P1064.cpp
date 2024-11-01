#include <stdio.h>
#include <stdlib.h>

#define MAXN 32001
#define MAXM 61

int dp[MAXN];
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i <= n; ++i) {
        dp[i] = -1;
    }
    dp[0] = 0;

    for (int i = 1; i <= m; ++i) {
        int v, p, q;
        scanf("%d %d %d", &v, &p, &q);
        if (q == 0) {
            for (int j = n; j >= v; --j) {
                if (dp[j - v] != -1 && dp[j] < dp[j - v] + v * p) {
                    dp[j] = dp[j - v] + v * p;
                }
            }
        } else {
            for (int j = n; j >= v; --j) {
                if (dp[j - v] != -1) {
                    dp[j] = dp[j - v];
                }
            }
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}