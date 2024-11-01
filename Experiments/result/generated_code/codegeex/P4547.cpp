#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

int n, m;
int edge[32][32];
int match[32];
int vis[32];

int dfs(int u) {
    for (int v = 1; v <= n; v++) {
        if (edge[u][v] && !vis[v]) {
            vis[v] = 1;
            if (!match[v] || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int t, a1, b1, a2, b2;
        scanf("%d", &t);
        if (t == 0) {
            scanf("%d%d", &a1, &b1);
            edge[a1][b1] = 1;
        } else if (t == 1) {
            scanf("%d%d%d%d", &a1, &b1, &a2, &b2);
            edge[a1][b1] = edge[a2][b2] = 1;
        } else if (t == 2) {
            scanf("%d%d%d%d", &a1, &b1, &a2, &b2);
            edge[a1][b1] = edge[a2][b2] = -1;
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i)) {
            ans++;
        }
    }

    printf("%d\n", (1LL << n) * ans % MOD);
    return 0;
}