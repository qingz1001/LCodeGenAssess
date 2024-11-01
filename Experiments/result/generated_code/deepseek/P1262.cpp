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

void dfs(int u) {
    visited[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!visited[v]) {
            dfs(v);
        }
    }
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
        minCost[i] = INT_MAX;
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

    for (int i = 1; i <= n; i++) {
        if (spies[i].cost != INT_MAX) {
            for (int j = 1; j <= n; j++) {
                visited[j] = 0;
            }
            dfs(i);
            for (int j = 1; j <= n; j++) {
                if (visited[j]) {
                    minCost[j] = (minCost[j] < spies[i].cost) ? minCost[j] : spies[i].cost;
                }
            }
        }
    }

    int totalCost = 0;
    int unvisitedSpy = -1;
    for (int i = 1; i <= n; i++) {
        if (minCost[i] == INT_MAX) {
            if (unvisitedSpy == -1 || unvisitedSpy > i) {
                unvisitedSpy = i;
            }
        } else {
            totalCost += minCost[i];
        }
    }

    if (unvisitedSpy == -1) {
        printf("YES\n%d\n", totalCost);
    } else {
        printf("NO\n%d\n", unvisitedSpy);
    }

    return 0;
}