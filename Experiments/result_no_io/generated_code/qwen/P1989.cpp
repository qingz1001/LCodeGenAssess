#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int adj[MAXN][MAXN];

void add_edge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;
}

long long count_triangles() {
    long long count = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (adj[i][j]) {
                for (int k = 1; k <= n; ++k) {
                    if (adj[j][k] && adj[k][i]) {
                        count++;
                    }
                }
            }
        }
    }
    return count / 6;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    printf("%lld\n", count_triangles());
    return 0;
}