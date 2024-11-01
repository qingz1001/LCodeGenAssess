#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edgeIndex = 0;
int degree[MAXN];
int n, p[MAXN];
double k;

void addEdge(int from, int to) {
    edges[edgeIndex].to = to;
    edges[edgeIndex].next = head[from];
    head[from] = edgeIndex++;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
        degree[u]++;
        degree[v]++;
    }
    scanf("%lf", &k);

    double totalProfit = 0.0;
    for (int i = 0; i < n; i++) {
        if (degree[i] == 1) {
            totalProfit += p[i] * k;
        }
    }

    printf("%.1f\n", totalProfit);

    return 0;
}