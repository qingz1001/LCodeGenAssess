#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005
#define MAXQ 25

double dp[MAXN][MAXQ];
int n, m, deg[MAXN];
int head[MAXN], nxt[MAXM], ver[MAXM], edge[MAXM];
int q[MAXN], l, r;
int fa[MAXN], sz[MAXN], h[MAXN], tot;
double ans;

void add(int x, int y, int z) {
    ver[tot] = y;
    edge[tot] = z;
    nxt[tot] = head[x];
    head[x] = tot++;
}

void dfs(int x) {
    q[l = r = 1] = x;
    while (l <= r) {
        int y = q[l++];
        for (int i = head[y]; i != -1; i = nxt[i]) {
            if (ver[i] != fa[y]) {
                fa[ver[i]] = y;
                dfs(ver[i]);
                sz[y] += sz[ver[i]];
                dp[y][0] += dp[ver[i]][0] + edge[i];
            }
        }
    }
    for (int i = 1; i <= sz[x]; i++) {
        dp[x][i] = dp[x][i - 1] + 1.0 * (dp[x][0] - dp[ver[q[r - i + 1]]][0] - edge[q[r - i + 1]]) / (sz[x] - i + 1);
    }
}

void dfs2(int x) {
    for (int i = head[x]; i != -1; i = nxt[i]) {
        if (ver[i] != fa[x]) {
            h[ver[i]] = h[x] + 1;
            double res = 1.0 * (dp[x][0] - dp[ver[i]][0] - edge[i]) / (deg[x] - 1);
            ans += 1.0 * (deg[ver[i]] - 1) * (h[ver[i]] + res) / deg[ver[i]];
            dfs2(ver[i]);
        }
    }
}

int main() {
    int x, y, z;
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        add(y, x, z);
        deg[x]++;
        deg[y]++;
    }
    if (m == n - 1) {
        dfs(1);
        printf("%.5lf\n", dp[1][0] / n);
    } else {
        h[1] = 1;
        dfs(1);
        ans = 0;
        dfs2(1);
        printf("%.5lf\n", ans);
    }
    return 0;
}