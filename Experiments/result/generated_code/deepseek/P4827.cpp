#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 10007
#define MAXN 50001
#define MAXK 151

typedef struct {
    int v, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
int n, k;
int dp[MAXN][MAXK], tmp[MAXK];
int size[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].v = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int u, int parent) {
    size[u] = 1;
    dp[u][0] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].v;
        if (v == parent) continue;
        dfs(v, u);
        size[u] += size[v];
        for (int j = 0; j <= k; j++) {
            dp[u][j] = (dp[u][j] + dp[v][j]) % MOD;
            if (j > 0) dp[u][j] = (dp[u][j] + dp[v][j - 1]) % MOD;
        }
    }
}

void dfs2(int u, int parent) {
    for (int i = 0; i <= k; i++) {
        tmp[i] = dp[u][i];
    }
    if (parent != -1) {
        tmp[0] = (tmp[0] + size[parent] - size[u]) % MOD;
        for (int i = 1; i <= k; i++) {
            tmp[i] = (tmp[i] + dp[parent][i] + dp[parent][i - 1] - dp[u][i] - dp[u][i - 1]) % MOD;
            if (i > 1) tmp[i] = (tmp[i] - dp[u][i - 2]) % MOD;
        }
    }
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].v;
        if (v == parent) continue;
        dfs2(v, u);
    }
    for (int i = 0; i <= k; i++) {
        dp[u][i] = tmp[i];
    }
}

int main() {
    scanf("%d %d", &n, &k);
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, -1);
    dfs2(1, -1);
    for (int i = 1; i <= n; i++) {
        int result = 0;
        for (int j = 0; j <= k; j++) {
            result = (result + dp[i][j] * dp[i][k - j]) % MOD;
        }
        printf("%d\n", (result + MOD) % MOD);
    }
    return 0;
}