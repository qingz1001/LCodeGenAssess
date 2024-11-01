#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MOD 10007

typedef struct {
    int to;
    int next;
} Edge;

int head[MAXN];
Edge edges[MAXN * 2];
int edgeCount;

void addEdge(int u, int v) {
    edges[edgeCount].to = v;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
    edges[edgeCount].to = u;
    edges[edgeCount].next = head[v];
    head[v] = edgeCount++;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);

    int weights[MAXN];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &weights[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    int maxJointWeight = 0;
    long long totalJointWeight = 0;

    for (int i = 1; i <= n; i++) {
        int maxWeight1 = 0, maxWeight2 = 0;
        for (int j = head[i]; j != -1; j = edges[j].next) {
            int neighbor = edges[j].to;
            if (weights[neighbor] > maxWeight1) {
                maxWeight2 = maxWeight1;
                maxWeight1 = weights[neighbor];
            } else if (weights[neighbor] > maxWeight2) {
                maxWeight2 = weights[neighbor];
            }
        }
        maxJointWeight = max(maxJointWeight, maxWeight1 * maxWeight2);
        for (int j = head[i]; j != -1; j = edges[j].next) {
            int neighbor = edges[j].to;
            totalJointWeight = (totalJointWeight + (long long)weights[i] * weights[neighbor]) % MOD;
        }
    }

    printf("%d %lld\n", maxJointWeight, totalJointWeight);

    return 0;
}