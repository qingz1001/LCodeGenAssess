#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 10007
#define MAXN 30005
#define MAXM 128

typedef struct {
    int to, next;
} Edge;

Edge edges[2 * MAXN];
int head[MAXN], edge_count;
int n, m, q;
int values[MAXN];
int dp[MAXN][MAXM];
int temp[MAXM];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int u, int parent) {
    dp[u][values[u]] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent) continue;
        dfs(v, u);
        for (int j = 0; j < m; j++) {
            temp[j] = dp[u][j];
        }
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                temp[j ^ k] = (temp[j ^ k] + dp[u][j] * dp[v][k]) % MOD;
            }
        }
        for (int j = 0; j < m; j++) {
            dp[u][j] = temp[j];
        }
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
    edge_count = 0;
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, -1);
    scanf("%d", &q);
    while (q--) {
        char op[10];
        scanf("%s", op);
        if (strcmp(op, "Change") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            update(x, y);
        } else if (strcmp(op, "Query") == 0) {
            int k;
            scanf("%d", &k);
            printf("%d\n", query(k));
        }
    }
    return 0;
}