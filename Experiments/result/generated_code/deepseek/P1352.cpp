#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 6005

int n;
int r[MAXN];
int dp[MAXN][2];
int vis[MAXN];
int head[MAXN], nxt[MAXN], to[MAXN], cnt;

void add_edge(int u, int v) {
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt++;
}

void dfs(int u) {
    vis[u] = 1;
    dp[u][0] = 0;
    dp[u][1] = r[u];
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        if (!vis[v]) {
            dfs(v);
            dp[u][0] += (dp[v][0] > dp[v][1] ? dp[v][0] : dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &r[i]);
    }
    memset(head, -1, sizeof(head));
    memset(nxt, -1, sizeof(nxt));
    memset(to, -1, sizeof(to));
    cnt = 0;
    for (int i = 1; i < n; i++) {
        int l, k;
        scanf("%d %d", &l, &k);
        add_edge(k, l);
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int max_val = dp[i][0] > dp[i][1] ? dp[i][0] : dp[i][1];
        if (max_val > ans) {
            ans = max_val;
        }
    }
    printf("%d\n", ans);
    return 0;
}