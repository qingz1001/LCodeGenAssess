#include <stdio.h>
#include <stdlib.h>

#define MAXN 500010
#define INF 0x3f3f3f3f

int n, m;
int a[MAXN], b[MAXN];
int dp[MAXN][2];

void solve() {
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = INF;
        dp[i][1] = -INF;
    }
    dp[1][b[a[1]]] = 0;

    for (int i = 2; i <= n; ++i) {
        int x = a[i];
        if (b[x]) {
            dp[i][1] = dp[i - 1][1] + 1;
        } else {
            dp[i][0] = dp[i - 1][0] + 1;
        }

        if (dp[i - 1][1] >= dp[i][0]) {
            dp[i][0] = dp[i - 1][1];
        }
        if (dp[i - 1][0] <= dp[i][1]) {
            dp[i][1] = dp[i - 1][0];
        }
    }

    int max_diff = -INF;
    for (int i = 1; i <= n; ++i) {
        max_diff = fmax(max_diff, abs(dp[i][0]));
        max_diff = fmax(max_diff, abs(dp[i][1]));
    }

    printf("%d\n", max_diff);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &a[i], &b[i]);
    }

    solve();

    return 0;
}