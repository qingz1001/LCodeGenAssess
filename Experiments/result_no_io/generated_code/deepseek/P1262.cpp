#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 3000
#define MAXR 8000

typedef struct {
    int id;
    int cost;
} Spy;

typedef struct {
    int to;
    int next;
} Edge;

Spy spies[MAXN + 1];
Edge edges[MAXR];
int head[MAXN + 1];
int visited[MAXN + 1];
int minCost[MAXN + 1];
int edgeCount = 0;

void addEdge(int from, int to) {
    edges[edgeCount].to = to;
    edges[edgeCount].next = head[from];
    head[from] = edgeCount++;
}

int dfs(int u) {
    if (visited[u]) return minCost[u];
    visited[u] = 1;
    minCost[u] = spies[u].cost;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!visited[v]) {
            int cost = dfs(v);
            if (cost != INT_MAX) {
                minCost[u] = (minCost[u] < cost) ? minCost[u] : cost;
            }
        }
    }
    return minCost[u];
}

int main() {
    int n, p, r;
    scanf("%d", &n);
    scanf("%d", &p);

    for (int i = 1; i <= n; i++) {
        spies[i].id = i;
        spies[i].cost = INT_MAX;
        head[i] = -1;
        visited[i] = 0;
    }

    for (int i = 0; i < p; i++) {
        int id, cost;
        scanf("%d %d", &id, &cost);
        spies[id].cost = cost;
    }

    scanf("%d", &r);
    for (int i = 0; i < r; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        addEdge(from, to);
    }

    int totalCost = 0;
    int uncontrol = -1;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            int cost = dfs(i);
            if (cost == INT_MAX) {
                uncontrol = i;
                break;
            }
            totalCost += cost;
        }
    }

    if (uncontrol == -1) {
        printf("YES\n%d\n", totalCost);
    } else {
        printf("NO\n%d\n", uncontrol);
    }

    return 0;
}