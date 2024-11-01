#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000

int parent[MAX_N + 1];
int depth[MAX_N + 1];

void init() {
    parent[1] = 1;
    depth[1] = 0;
    for (int i = 2; i <= MAX_N; i++) {
        if (i % 2 == 0) {
            parent[i] = i / 2;
            depth[i] = depth[i / 2] + 1;
        } else {
            parent[i] = (i + 1) / 2;
            depth[i] = depth[(i + 1) / 2] + 1;
        }
    }
}

int find_lca(int a, int b) {
    while (depth[a] > depth[b]) {
        a = parent[a];
    }
    while (depth[b] > depth[a]) {
        b = parent[b];
    }
    while (a != b) {
        a = parent[a];
        b = parent[b];
    }
    return a;
}

int main() {
    int m, a, b;
    init();
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        printf("%d\n", find_lca(a, b));
    }
    return 0;
}