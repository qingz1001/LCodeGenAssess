#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 501
#define MAX_M 1002

typedef struct {
    int u, v;
} Edge;

int parent[MAX_N];
Edge edges[MAX_M];
int n, m;

void init() {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    parent[find(x)] = find(y);
}

bool solve() {
    init();
    int count = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v;
        if (find(u) != find(v)) {
            unite(u, v);
            count++;
        }
    }
    return count == n - 1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &edges[i].u, &edges[i].v);
        }
        printf("%s\n", solve() ? "Yes" : "No");
    }
    return 0;
}