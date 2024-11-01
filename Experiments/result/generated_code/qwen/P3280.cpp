#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define INF 1e9

typedef struct {
    int u, v, w;
} Edge;

int n, m, q;
int order[MAXN];
int b[MAXN];
Edge edges[MAXN * 2];
int train_stations[MAXN];

int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void unionSet(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    if (xset != yset)
        parent[xset] = yset;
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &order[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        edges[i + m].u = edges[i].v;
        edges[i + m].v = edges[i].u;
        edges[i + m].w = edges[i].w;
    }
    for (int i = 0; i < q; i++) {
        scanf("%d", &train_stations[i]);
    }

    int parent[n];
    for (int i = 0; i < n; i++)
        parent[i] = -1;

    int result[q];
    for (int i = 0; i < q; i++) {
        int station = train_stations[i] - 1;
        for (int j = 0; j < 2 * m; j++) {
            int u = edges[j].u - 1;
            int v = edges[j].v - 1;
            if (find(parent, u) == find(parent, v)) {
                if (u == station || v == station) {
                    unionSet(parent, u, v);
                }
            }
        }
        int total = 0;
        for (int j = 0; j < n; j++) {
            if (find(parent, j) == find(parent, station)) {
                total += b[j];
            }
        }
        result[i] = total / 2;
    }

    for (int i = 0; i < q; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}