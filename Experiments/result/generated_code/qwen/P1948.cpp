#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define MAXP 10001

typedef struct {
    int a, b, l;
} Edge;

int parent[MAXN];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_set(int x, int y) {
    parent[find(x)] = find(y);
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->l - ((Edge *)b)->l;
}

int main() {
    int n, p, k;
    scanf("%d %d %d", &n, &p, &k);

    Edge edges[MAXP];
    for (int i = 0; i < p; i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].l);
    }

    qsort(edges, p, sizeof(Edge), compare);

    for (int i = 0; i <= n; i++) {
        parent[i] = i;
    }

    int used = 0;
    int max_length = 0;

    for (int i = 0; i < p; i++) {
        int root_a = find(edges[i].a);
        int root_b = find(edges[i].b);

        if (root_a != root_b) {
            union_set(root_a, root_b);
            used++;
            max_length = edges[i].l;
            if (used >= n - 1 + k) {
                break;
            }
        }
    }

    if (used < n - 1 + k) {
        printf("-1\n");
    } else {
        printf("%d\n", max_length);
    }

    return 0;
}