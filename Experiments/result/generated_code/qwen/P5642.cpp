#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

typedef struct {
    int u, v, w;
} Edge;

int parent[300005];
int rank[300005];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    init(n);

    Edge edges[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    long long result = 0;

    for (int w = 1; w <= 1e9; w++) {
        int used[n + 1][n + 1];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                used[i][j] = 0;
            }
        }

        for (int i = 0; i < m; i++) {
            if (edges[i].w >= w) {
                used[edges[i].u][edges[i].v] = 1;
                used[edges[i].v][edges[i].u] = 1;
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (!used[i][j]) {
                    merge(i, j);
                }
            }
        }

        int components = 0;
        for (int i = 1; i <= n; i++) {
            if (find(i) == i) {
                components++;
            }
        }

        result += (long long)(components * (components - 1)) / 2;
        result %= MOD;
    }

    printf("%lld\n", result);

    return 0;
}