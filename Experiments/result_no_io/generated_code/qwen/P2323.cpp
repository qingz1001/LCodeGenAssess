#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10005
#define MAX_M 20005

typedef struct {
    int a, b, c1, c2;
} Edge;

int n, k, m;
Edge edges[MAX_M];
int parent[MAX_N], rank[MAX_N];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->c1 - edgeB->c1;
}

int main() {
    scanf("%d %d %d", &n, &k, &m);

    for (int i = 0; i < m - 1; i++) {
        scanf("%d %d %d %d", &edges[i].a, &edges[i].b, &edges[i].c1, &edges[i].c2);
    }

    qsort(edges, m - 1, sizeof(Edge), compare);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int count = 0;
    int max_cost = 0;
    int used_edges[m - 1];

    for (int i = 0; i < m - 1; i++) {
        int u = edges[i].a;
        int v = edges[i].b;
        int c1 = edges[i].c1;
        int c2 = edges[i].c2;

        if (find(u) != find(v)) {
            union_set(u, v);
            count++;
            if (count >= k) {
                max_cost = c2;
                used_edges[count - 1] = i + 1;
                if (count == n - 1)
                    break;
            } else {
                max_cost = c1;
                used_edges[count - 1] = i + 1;
            }
        }
    }

    printf("%d\n", max_cost);

    for (int i = 0; i < n - 1; i++) {
        printf("%d %d\n", used_edges[i], (i < k ? 1 : 2));
    }

    return 0;
}