#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 501
#define MAX_M 1002

int parent[MAX_N];
int rank[MAX_N];

void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank[a] < rank[b])
            parent[a] = b;
        else {
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }
}

bool solve(int n, int m, int edges[][2]) {
    for (int i = 1; i <= n; i++)
        make_set(i);

    int components = n;
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        if (find_set(u) != find_set(v)) {
            union_sets(u, v);
            components--;
        }
    }

    return m <= 2 * (n - 1) - components + 1;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);

        int edges[MAX_M][2];
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &edges[i][0], &edges[i][1]);
        }

        if (solve(n, m, edges)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}