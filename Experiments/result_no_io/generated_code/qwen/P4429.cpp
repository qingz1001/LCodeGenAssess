#include <stdio.h>
#include <stdlib.h>

#define MAXN 10010
#define MAXM 20010

int n, m;
int graph[MAXN][MAXN];
int degree[MAXN];

void add_edge(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
    degree[u]++;
    degree[v]++;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                graph[i][j] = 0;
            }
            degree[i] = 0;
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            add_edge(u, v);
        }

        int has_odd_degree = 0;
        for (int i = 1; i <= n; i++) {
            if (degree[i] % 2 != 0) {
                has_odd_degree++;
            }
        }

        if (has_odd_degree > 1) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}