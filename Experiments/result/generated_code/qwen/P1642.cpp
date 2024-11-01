#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

typedef struct {
    int u, v;
} Edge;

int n, m;
int w[MAXN], c[MAXN];
Edge edges[MAXN - 1];

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

void unionSet(int parent[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    parent[rootX] = rootY;
}

double maxProfitRatio() {
    int parent[n];
    for (int i = 0; i < n; i++)
        parent[i] = i;

    double totalWeight = 0, totalCost = 0;
    for (int i = 0; i < n - 1; i++) {
        int rootU = find(parent, edges[i].u - 1);
        int rootV = find(parent, edges[i].v - 1);
        if (rootU != rootV) {
            unionSet(parent, rootU, rootV);
            totalWeight += w[edges[i].u - 1] + w[edges[i].v - 1];
            totalCost += c[edges[i].u - 1] + c[edges[i].v - 1];
        }
    }

    return totalWeight / totalCost;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &w[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &c[i]);
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
    }

    printf("%.1f\n", maxProfitRatio());

    return 0;
}