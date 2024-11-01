#include <stdio.h>
#include <stdlib.h>

#define MAXN 105
#define MAXP 13
#define INF 1e9

int n, p;
int graph[MAXN][MAXN];
int cost[MAXN][MAXP];
int benefit[MAXP];
int influence[MAXP][MAXP];

void dfs(int node, int parent, int mask, long long *max_profit) {
    long long profit = 0;
    for (int i = 0; i < p; i++) {
        if ((mask & (1 << i)) != 0) {
            profit += cost[node][i];
        }
    }
    for (int i = 0; i < p; i++) {
        if ((mask & (1 << i)) != 0) {
            for (int j = 0; j < p; j++) {
                if (influence[i][j] != 0 && (mask & (1 << j)) != 0) {
                    profit += influence[i][j];
                }
            }
        }
    }
    if (node == 1) {
        profit += benefit[0];
    } else {
        for (int i = 1; i <= n; i++) {
            if (graph[node][i] != 0) {
                dfs(i, node, mask, max_profit);
            }
        }
    }
    *max_profit = (*max_profit > profit ? *max_profit : profit);
}

int main() {
    scanf("%d %d", &n, &p);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= p; j++) {
            scanf("%d", &cost[i][j]);
        }
    }
    for (int i = 1; i <= p; i++) {
        scanf("%d", &benefit[i]);
    }
    for (int i = 1; i <= p; i++) {
        for (int j = 1; j <= p; j++) {
            influence[i][j] = 0;
        }
    }
    int t;
    scanf("%d", &t);
    for (int k = 0; k < t; k++) {
        int v, c;
        scanf("%d %d", &v, &c);
        for (int l = 0; l < c; l++) {
            int x;
            scanf("%d", &x);
            influence[v][x]++;
        }
    }
    long long max_profit = -INF;
    for (int i = 1; i <= n; i++) {
        dfs(i, -1, (1 << p) - 1, &max_profit);
    }
    printf("%lld\n", max_profit);
    return 0;
}