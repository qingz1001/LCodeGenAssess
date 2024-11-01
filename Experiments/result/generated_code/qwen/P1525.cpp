#include <stdio.h>
#include <stdlib.h>

#define MAXN 20005
#define MAXM 100005

typedef struct {
    int a, b, c;
} Edge;

int n, m;
Edge edges[MAXM];
int parent[MAXN];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    parent[find(x)] = find(y);
}

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeB->c - edgeA->c;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].c);
    }

    qsort(edges, m, sizeof(Edge), compare);

    for (int i = 1; i <= n; i++)
        parent[i] = i;

    int max_conflict = 0;
    for (int i = 0; i < m; i++) {
        int root_a = find(edges[i].a);
        int root_b = find(edges[i].b);
        if (root_a != root_b) {
            union_set(root_a, root_b);
        } else {
            max_conflict = edges[i].c;
            break;
        }
    }

    printf("%d\n", max_conflict);

    return 0;
}