#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1024
#define MAXM 2048

int n, m;
int w[MAXN][MAXN], f[MAXN][MAXN];
int dp[MAXN][MAXN];

void dfs(int u, int l, int r) {
    if (l == r) {
        dp[u][0] = 0;
        dp[u][1] = w[u][0];
        return;
    }
    int mid = (l + r) / 2;
    dfs(u * 2, l, mid);
    dfs(u * 2 + 1, mid + 1, r);
    for (int i = 0; i <= mid - l + 1; i++) {
        for (int j = 0; j <= r - mid; j++) {
            dp[u][i + j] = 0;
            for (int k = 0; k <= i; k++) {
                dp[u][i + j] = fmax(dp[u][i + j], dp[u * 2][k] + dp[u * 2 + 1][i - k + j]);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    int cnt = 1 << (n - 1);
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < n - 1; j++) {
            scanf("%d", &w[i + cnt][j]);
        }
    }
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < n - 1; j++) {
            scanf("%d", &f[i + cnt][j]);
        }
    }
    dfs(1, 1, cnt);
    int ans = 0;
    for (int i = 0; i <= m; i++) {
        ans = fmax(ans, dp[1][i]);
    }
    printf("%d\n", ans);
    return 0;
}