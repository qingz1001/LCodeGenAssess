#include <stdio.h>
#include <string.h>

#define MAXN 1005
#define MAXW 1005

int dp[MAXN][MAXW];
char s[MAXN];

void dfs(int len, int w) {
    if (len > w) return;
    dp[len][len] = 1;
    for (int i = 1; i <= len - 1; ++i) {
        dfs(i, w);
        dfs(len - i, w);
        for (int j = 0; j <= w - len; ++j) {
            dp[j + len][w] += dp[i][j] * dp[len - i][w - len];
        }
    }
}

int main() {
    int t, n, w;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &w);
        scanf("%s", s);
        memset(dp, 0, sizeof(dp));
        dfs(n, w);
        int ans = 0;
        for (int i = 1; i <= w; ++i) {
            if (dp[i][w]) ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}