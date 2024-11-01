#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

struct Edge {
    int u, v;
    double weight;
};

int compare(const void *a, const void *b) {
    struct Edge *edge1 = (struct Edge *)a;
    struct Edge *edge2 = (struct Edge *)b;
    return (edge1->weight > edge2->weight);
}

int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    else
        return find(parent, parent[i]);
}

void unionSets(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

double calculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    int n, m, s, t;
    scanf("%d", &n);
    int x[MAX], y[MAX];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    scanf("%d", &m);
    struct Edge edges[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
        edges[i].u--;
        edges[i].v--;
        edges[i].weight = calculateDistance(x[edges[i].u], y[edges[i].u], x[edges[i].v], y[edges[i].v]);
    }
    scanf("%d %d", &s, &t);
    s--;
    t--;

    qsort(edges, m, sizeof(struct Edge), compare);

    int parent[n];
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }

    int i = 0;
    int numEdges = 0;
    while (numEdges < n - 1 && i < m) {
        int u = edges[i].u;
        int v = edges[i].v;
        int setU = find(parent, u);
        int setV = find(parent, v);
        if (setU != setV) {
            unionSets(parent, setU, setV);
            numEdges++;
        }
        i++;
    }

    double shortestPath = calculateDistance(x[s], y[s], x[t], y[t]);
    for (i = 0; i < m; i++) {
        if (find(parent, edges[i].u) == find(parent, s) && find(parent, edges[i].v) == find(parent, t)) {
            shortestPath = edges[i].weight;
            break;
        }
    }

    printf("%.2lf\n", shortestPath);

    return 0;
}