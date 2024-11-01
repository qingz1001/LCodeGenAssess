#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

typedef struct {
    int u, v, w;
} Edge;

int compare(const void *a, const void *b) {
    return ((Edge *)b)->w - ((Edge *)a)->w;
}

int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void unionSet(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

long long maxWeight(int parent[], int n) {
    long long weight = 0;
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1)
            weight += 1LL * (find(parent, i) - i + 1);
    }
    return weight;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Edge edges[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        edges[i].u--;
        edges[i].v--;
    }

    qsort(edges, m, sizeof(Edge), compare);

    int parent[n];
    for (int i = 0; i < n; i++)
        parent[i] = -1;

    long long result = 0;
    for (int i = 0; i < m; i++) {
        int x = edges[i].u;
        int y = edges[i].v;
        int px = find(parent, x);
        int py = find(parent, y);

        if (px != py) {
            unionSet(parent, px, py);
            long long currentWeight = maxWeight(parent, n);
            long long nextWeight = currentWeight + 1;
            result = (result + nextWeight - currentWeight) % MOD;
        }
    }

    printf("%lld\n", result);

    return 0;
}