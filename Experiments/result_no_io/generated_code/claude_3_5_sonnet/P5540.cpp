#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 201
#define MAXM 10001
#define INF 1e18

typedef long long ll;

struct Edge {
    int u, v, a, b;
    double w;
} edges[MAXM];

int n, m;
int parent[MAXN];

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unite(int x, int y) {
    parent[find(x)] = find(y);
}

int cmp(const void *a, const void *b) {
    struct Edge *ea = (struct Edge *)a;
    struct Edge *eb = (struct Edge *)b;
    return (ea->w > eb->w) - (ea->w < eb->w);
}

double kruskal(double lambda) {
    for (int i = 0; i < m; i++) {
        edges[i].w = edges[i].a - lambda * edges[i].b;
    }
    qsort(edges, m, sizeof(struct Edge), cmp);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    double suma = 0, sumb = 0;
    for (int i = 0; i < m; i++) {
        if (find(edges[i].u) != find(edges[i].v)) {
            unite(edges[i].u, edges[i].v);
            suma += edges[i].a;
            sumb += edges[i].b;
        }
    }

    return suma - lambda * sumb;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].a, &edges[i].b);
    }

    double l = 0, r = 256;
    while (r - l > 1e-9) {
        double mid = (l + r) / 2;
        if (kruskal(mid) > 0) {
            l = mid;
        } else {
            r = mid;
        }
    }

    ll suma = 0, sumb = 0;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    for (int i = 0; i < m; i++) {
        edges[i].w = edges[i].a - l * edges[i].b;
    }
    qsort(edges, m, sizeof(struct Edge), cmp);

    for (int i = 0; i < m; i++) {
        if (find(edges[i].u) != find(edges[i].v)) {
            unite(edges[i].u, edges[i].v);
            suma += edges[i].a;
            sumb += edges[i].b;
        }
    }

    printf("%lld %lld\n", suma, sumb);

    return 0;
}