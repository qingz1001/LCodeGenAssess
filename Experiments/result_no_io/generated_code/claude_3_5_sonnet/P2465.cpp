#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 101
#define MAX_P 13
#define MAX_T 4096
#define INF 0x3f3f3f3f

int n, p, t;
int graph[MAX_N][MAX_N];
int cost[MAX_N][MAX_P];
int profit[MAX_T];
int dp[1 << MAX_P][MAX_N];
int parent[MAX_N];

void init() {
    memset(graph, 0x3f, sizeof(graph));
    memset(profit, 0, sizeof(profit));
    for (int i = 0; i < n; i++) {
        graph[i][i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px != py) {
        parent[py] = px;
    }
}

void floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &p);
    init();

    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;
        graph[x][y] = graph[y][x] = 1;
        unite(x, y);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        int v, c, mask = 0;
        scanf("%d %d", &v, &c);
        for (int j = 0; j < c; j++) {
            int x;
            scanf("%d", &x);
            mask |= (1 << (x - 1));
        }
        profit[mask] += v;
    }

    floyd();

    memset(dp, -0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int mask = 0; mask < (1 << p); mask++) {
        for (int i = 0; i < n; i++) {
            if (dp[mask][i] == -INF) continue;
            for (int j = 0; j < p; j++) {
                if (mask & (1 << j)) continue;
                int new_mask = mask | (1 << j);
                for (int k = 0; k < n; k++) {
                    int new_profit = dp[mask][i] - cost[k][j];
                    for (int submask = new_mask; submask; submask = (submask - 1) & new_mask) {
                        if (graph[0][i] >= graph[0][k]) {
                            new_profit += profit[submask];
                        }
                    }
                    if (new_profit > dp[new_mask][k]) {
                        dp[new_mask][k] = new_profit;
                    }
                }
            }
        }
    }

    int ans = -INF;
    for (int i = 0; i < n; i++) {
        if (dp[(1 << p) - 1][i] > ans) {
            ans = dp[(1 << p) - 1][i];
        }
    }

    printf("%d\n", ans);

    return 0;
}