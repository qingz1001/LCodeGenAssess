#include <stdio.h>
#include <stdlib.h>

#define MAXN 151

int n, p;
int dp[MAXN][MAXN];
int son[MAXN][MAXN];
int size[MAXN];
int ans = 0x7f7f7f7f;

void dfs(int u, int fa) {
    size[u] = 1;
    for (int i = 1; i <= son[u][0]; i++) {
        int v = son[u][i];
        if (v == fa) continue;
        dfs(v, u);
        size[u] += size[v];
        for (int j = size[u]; j >= 1; j--)
            for (int k = 0; k <= size[v]; k++) {
                if (j - k < 0 || k < 0) continue;
                dp[u][j] = (dp[u][j] < dp[u][j - k] + dp[v][k]) ? dp[u][j] : dp[u][j - k] + dp[v][k];
            }
    }
    if (size[u] - 1 >= p) {
        for (int j = p; j <= size[u]; j++)
            ans = (ans < dp[u][j]) ? ans : dp[u][j];
    }
}

int main() {
    scanf("%d%d", &n, &p);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        son[u][0]++;
        son[u][son[u][0]] = v;
        son[v][0]++;
        son[v][son[v][0]] = u;
    }
    for (int i = 1; i <= n; i++) {
        dp[i][1] = 0;
        for (int j = 2; j <= n; j++)
            dp[i][j] = 0x7f7f7f7f;
    }
    dfs(1, 0);
    printf("%d\n", ans);
    return 0;
}