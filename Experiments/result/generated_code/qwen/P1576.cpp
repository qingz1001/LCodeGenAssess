#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2005
#define MAXM 100005

typedef struct {
    int to;
    double cost;
} Edge;

Edge edges[MAXM];
int parent[MAXN];

double dist[MAXN];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_sets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY)
        parent[rootX] = rootY;
}

double min_cost_flow(int n, int m, int s, int t) {
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        dist[i] = INT_MAX;
    }
    dist[s] = 0;

    while (1) {
        int u = -1;
        double minDist = INT_MAX;
        for (int v = 1; v <= n; v++) {
            if (dist[v] < minDist && !visited[v]) {
                minDist = dist[v];
                u = v;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int i = 0; i < m; i++) {
            if (edges[i].to == u && dist[edges[i].to] > dist[edges[i].from] + edges[i].cost) {
                dist[edges[i].to] = dist[edges[i].from] + edges[i].cost;
                parent[edges[i].to] = edges[i].from;
            }
        }
    }

    if (dist[t] == INT_MAX)
        return -1;

    double flow = 0;
    double cost = 0;
    while (flow < 100) {
        int u = t;
        double pathFlow = INT_MAX;
        while (u != s) {
            pathFlow = fmin(pathFlow, 100 - flow);
            u = parent[u];
        }

        flow += pathFlow;
        cost += pathFlow * dist[t];

        u = t;
        while (u != s) {
            int prev = parent[u];
            edges[i].cost -= pathFlow * edges[i].cost / 100;
            i++;
            u = prev;
        }
    }

    return cost;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int x, y;
        double z;
        scanf("%d %d %lf", &x, &y, &z);
        edges[i].to = y;
        edges[i].cost = z;
    }

    int A, B;
    scanf("%d %d", &A, &B);

    printf("%.8f\n", min_cost_flow(n, m, A, B));

    return 0;
}