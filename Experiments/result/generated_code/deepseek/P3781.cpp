#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 10007

typedef struct {
    int to, next;
} Edge;

Edge edges[200005];
int head[100005], edge_count = 0;
int values[100005];
int n, m, q;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int dp[100005][128];
int temp[128];

void dfs(int u, int parent) {
    dp[u][values[u]] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent) continue;
        dfs(v, u);
        memcpy(temp, dp[u], sizeof(temp));
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                temp[j ^ k] = (temp[j ^ k] + dp[u][j] * dp[v][k]) % MOD;
            }
        }
        memcpy(dp[u], temp, sizeof(temp));
    }
}

void update(int x, int y) {
    values[x] = y;
    memset(dp, 0, sizeof(dp));
    dfs(1, -1);
}

int query(int k) {
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = (result + dp[i][k]) % MOD;
    }
    return result;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &values[i]);
    }
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    scanf("%d", &q);
    dfs(1, -1);
    while (q--) {
        char op[10];
        int x, y;
        scanf("%s", op);
        if (strcmp(op, "Change") == 0) {
            scanf("%d %d", &x, &y);
            update(x, y);
        } else if (strcmp(op, "Query") == 0) {
            scanf("%d", &x);
            printf("%d\n", query(x));
        }
    }
    return 0;
}