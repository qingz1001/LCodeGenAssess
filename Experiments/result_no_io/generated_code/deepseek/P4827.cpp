#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 10007
#define MAXN 50005
#define MAXK 155

typedef struct {
    int v, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], cnt;
int n, k;
int dp[MAXN][MAXK], tmp[MAXK];
int size[MAXN];

void addEdge(int u, int v) {
    edges[cnt].v = v;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u, int fa) {
    size[u] = 1;
    dp[u][0] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].v;
        if (v == fa) continue;
        dfs(v, u);
        size[u] += size[v];
        for (int j = 0; j <= k; j++) {
            dp[u][j] = (dp[u][j] + dp[v][j]) % MOD;
            if (j > 0) dp[u][j] = (dp[u][j] + dp[v][j - 1]) % MOD;
        }
    }
}

void dfs2(int u, int fa) {
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].v;
        if (v == fa) continue;
        memcpy(tmp, dp[u], sizeof(dp[u]));
        for (int j = 0; j <= k; j++) {
            tmp[j] = (tmp[j] - dp[v][j] + MOD) % MOD;
            if (j > 0) tmp[j] = (tmp[j] - dp[v][j - 1] + MOD) % MOD;
        }
        for (int j = 0; j <= k; j++) {
            dp[v][j] = (dp[v][j] + tmp[j]) % MOD;
            if (j > 0) dp[v][j] = (dp[v][j] + tmp[j - 1]) % MOD;
        }
        dfs2(v, u);
    }
}

int main() {
    scanf("%d %d", &n, &k);
    memset(head, -1, sizeof(head));
    cnt = 0;
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        int ans = 0;
        for (int j = 0; j <= k; j++) {
            ans = (ans + dp[i][j]) % MOD;
        }
        printf("%d\n", ans);
    }
    return 0;
}