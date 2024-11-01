#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define MAXP 12

int n, p;
int graph[MAXN][MAXN];
int cost[MAXN][MAXP];
int benefit[MAXP][MAXP];
int t;

void dfs(int node, int parent, int mask, int *max_profit) {
    int profit = 0;
    for (int i = 0; i < p; i++) {
        if ((mask & (1 << i)) != 0) {
            profit += cost[node][i];
            for (int j = 0; j < p; j++) {
                if ((mask & (1 << j)) != 0 && benefit[i][j] > 0) {
                    profit += benefit[i][j];
                }
            }
        }
    }
    *max_profit = (*max_profit > profit) ? *max_profit : profit;
    for (int i = 0; i < n; i++) {
        if (graph[node][i] != 0 && i != parent) {
            dfs(i, node, mask, max_profit);
        }
    }
}

int main() {
    scanf("%d %d", &n, &p);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x - 1][y - 1] = 1;
        graph[y - 1][x - 1] = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            scanf("%d", &cost[i][j]);
        }
    }
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) {
            benefit[i][j] = 0;
        }
    }
    for (int i = 0; i < t; i++) {
        int v, c;
        scanf("%d %d", &v, &c);
        int ids[c];
        for (int j = 0; j < c; j++) {
            scanf("%d", &ids[j]);
            ids[j]--;
        }
        for (int j = 0; j < c; j++) {
            for (int k = j + 1; k < c; k++) {
                benefit[ids[j]][ids[k]] += v;
                benefit[ids[k]][ids[j]] += v;
            }
        }
    }
    int max_profit = 0;
    for (int i = 0; i < n; i++) {
        dfs(i, -1, (1 << p) - 1, &max_profit);
    }
    printf("%d\n", max_profit);
    return 0;
}