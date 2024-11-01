#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 105
#define MAXP 12
#define MAX_STATES (1 << MAXP)

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count;
int cost[MAXN][MAXP];
int dp[MAXN][MAX_STATES];
int influence[MAX_STATES];
int n, p;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int u, int parent) {
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent) continue;
        dfs(v, u);
        for (int state = 0; state < (1 << p); state++) {
            dp[u][state] += dp[v][0];
        }
    }

    for (int state = 0; state < (1 << p); state++) {
        int current_cost = 0;
        for (int i = 0; i < p; i++) {
            if (state & (1 << i)) {
                current_cost += cost[u][i];
            }
        }
        dp[u][state] += influence[state];
        dp[u][state] -= current_cost;
    }

    for (int state = 0; state < (1 << p); state++) {
        for (int subset = state; subset; subset = (subset - 1) & state) {
            dp[u][state] = dp[u][state] > (dp[u][subset] + dp[u][state ^ subset]) ? dp[u][state] : (dp[u][subset] + dp[u][state ^ subset]);
        }
    }
}

int main() {
    memset(head, -1, sizeof(head));
    memset(dp, 0, sizeof(dp));
    memset(influence, 0, sizeof(influence));

    scanf("%d %d", &n, &p);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < p; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        int v, c;
        scanf("%d %d", &v, &c);
        int state = 0;
        for (int j = 0; j < c; j++) {
            int x;
            scanf("%d", &x);
            state |= (1 << (x - 1));
        }
        influence[state] += v;
    }

    dfs(1, -1);

    int max_profit = dp[1][(1 << p) - 1];
    printf("%d\n", max_profit);

    return 0;
}