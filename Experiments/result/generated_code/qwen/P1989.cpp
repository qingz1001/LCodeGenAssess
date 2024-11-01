#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int graph[MAXN][MAXN];

void addEdge(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
}

long long countTriangles() {
    long long count = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (graph[i][j]) {
                for (int k = j + 1; k <= n; ++k) {
                    if (graph[j][k] && graph[k][i]) {
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
        addEdge(u, v);
    }
    printf("%lld\n", countTriangles());
    return 0;
}