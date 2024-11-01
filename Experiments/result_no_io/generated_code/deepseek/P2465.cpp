#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 105
#define MAXP 13
#define MAX_STATES (1 << MAXP)

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_cnt;
int cost[MAXN][MAXP];
int dp[MAXN][MAX_STATES];
int influence[MAX_STATES];
int n, p;

void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void dfs(int u, int parent) {
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent) continue;
        dfs(v, u);
        for (int state = 0; state < (1 << p); state++) {
            int min_cost = 1e9;
            for (int sub_state = state; sub_state; sub_state = (sub_state - 1) & state) {
                int current_cost = dp[v][sub_state] + dp[u][state ^ sub_state];
                if (current_cost < min_cost) min_cost = current_cost;
            }
            dp[u][state] += min_cost;
        }
    }
    for (int state = 0; state < (1 << p); state++) {
        int current_cost = 0;
        for (int i = 0; i < p; i++) {
            if (state & (1 << i)) {
                current_cost += cost[u][i];
            }
        }
        dp[u][state] += current_cost;
    }
}

int main() {
    scanf("%d %d", &n, &p);
    memset(head, -1, sizeof(head));
    edge_cnt = 0;

    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < p; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    int t;
    scanf("%d", &t);
    memset(influence, 0, sizeof(influence));
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

    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        for (int state = 0; state < (1 << p); state++) {
            dp[i][state] = 0;
        }
    }

    dfs(1, -1);

    int max_profit = -1e9;
    for (int state = 0; state < (1 << p); state++) {
        int total_profit = dp[1][state];
        for (int sub_state = state; sub_state; sub_state = (sub_state - 1) & state) {
            total_profit += influence[sub_state];
        }
        if (total_profit > max_profit) max_profit = total_profit;
    }

    printf("%d\n", max_profit);
    return 0;
}