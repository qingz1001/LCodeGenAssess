#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

struct Edge {
    int to, next;
    int weight;
} edges[MAXM];

int head[MAXN], edgeCount;
int n, m;
double dp[MAXN];

void addEdge(int u, int v, int w) {
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void dfs(int u, int parent) {
    double totalWeight = 0;
    int childCount = 0;

    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != parent) {
            dfs(v, u);
            totalWeight += dp[v];
            childCount++;
        }
    }

    if (childCount == 0) {
        dp[u] = 0;
    } else {
        dp[u] = totalWeight + 1.0 / childCount;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    edgeCount = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    double totalExpectation = 0;

    for (int i = 1; i <= n; i++) {
        memset(dp, 0, sizeof(dp));
        dfs(i, -1);
        totalExpectation += dp[i];
    }

    printf("%.5f\n", totalExpectation / n);
    return 0;
}