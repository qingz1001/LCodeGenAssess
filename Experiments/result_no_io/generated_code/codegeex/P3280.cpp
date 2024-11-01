#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 400005
#define MAXQ 100005

typedef struct Edge {
    int to, next, weight;
} Edge;

Edge edges[MAXM];
int head[MAXN], edgeCount;
int cityOrder[MAXN], cityLimit[MAXN], station[MAXN];
int n, m, q;
int dp[MAXN], parent[MAXN], inStack[MAXN], stackTop;
int *indexStack, *goldStack;

void addEdge(int u, int v, int w) {
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void dfs(int u) {
    parent[u] = -1;
    dp[u] = cityLimit[u];
    inStack[u] = 1;
    indexStack[stackTop++] = u;
    goldStack[stackTop - 1] = dp[u];

    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (dp[v] < dp[u] + edges[i].weight) {
            dp[v] = dp[u] + edges[i].weight;
            parent[v] = u;
        }
        if (dp[v] != goldStack[stackTop - 1]) {
            goldStack[stackTop - 1] = dp[v];
            indexStack[stackTop - 1] = v;
        }
        if (inStack[v]) {
            continue;
        }
        dfs(v);
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    memset(head, -1, sizeof(head));
    memset(dp, -1, sizeof(dp));
    memset(station, -1, sizeof(station));
    edgeCount = 0;
    stackTop = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &cityOrder[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &cityLimit[i]);
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    for (int i = 0; i < q; i++) {
        int s;
        scanf("%d", &s);
        station[s] = 1;
    }

    indexStack = (int *)malloc((n + 1) * sizeof(int));
    goldStack = (int *)malloc((n + 1) * sizeof(int));

    for (int i = 0; i < n; i++) {
        if (!inStack[cityOrder[i]]) {
            dfs(cityOrder[i]);
        }
    }

    int currentGold = 0;
    for (int i = 0; i < n; i++) {
        int city = cityOrder[i];
        if (cityLimit[city] < 0) {
            int sellAmount = -cityLimit[city];
            if (currentGold > sellAmount) {
                currentGold -= sellAmount;
                printf("%d\n", sellAmount);
            } else {
                printf("%d\n", currentGold);
                currentGold = 0;
            }
        } else {
            currentGold += cityLimit[city];
        }
    }

    free(indexStack);
    free(goldStack);

    return 0;
}