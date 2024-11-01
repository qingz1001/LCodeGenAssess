#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 110
#define MAXM 2147483647

int n, m, k;
double dp[MAXN][MAXM];

void init() {
    scanf("%d %d %d", &n, &m, &k);
}

void solve() {
    double ans = 0;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 1; k <= i; k++) {
                if (j >= abs(k - i)) {
                    dp[i][j] += dp[i - 1][j - abs(k - i)] / i;
                }
            }
        }
    }
    for (int i = m; i <= m; i++) {
        ans += dp[n][i];
    }
    printf("%.0lf\n", round(ans * pow(10, k)) / pow(10, k));
}

int main() {
    init();
    solve();
    return 0;
}