#include <stdio.h>
#include <stdlib.h>

#define MAXN 2005

int n, m;
int k[MAXN];
int graph[MAXN][MAXN];
int degree[MAXN];
int order[MAXN];
int min_order[MAXN];

void topological_sort() {
    int queue[MAXN], front = -1, rear = -1;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 0) {
            queue[++rear] = i;
        }
    }
    while (front != rear) {
        int u = queue[++front];
        order[u] = 1;
        for (int v = 1; v <= n; ++v) {
            if (graph[u][v]) {
                if (--degree[v] == 0) {
                    queue[++rear] = v;
                }
            }
        }
    }
}

void dfs(int u, int seq[]) {
    if (seq[u] != 0) return;
    seq[u] = order[u];
    for (int v = 1; v <= n; ++v) {
        if (graph[u][v]) {
            dfs(v, seq);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &k[i]);
    }
    for (int i = 1; i <= m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = 1;
        degree[b]++;
    }

    topological_sort();

    int seq[n + 1];
    for (int i = 1; i <= n; ++i) {
        seq[i] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        dfs(i, seq);
    }

    printf("%d", seq[1]);
    for (int i = 2; i <= n; ++i) {
        printf(" %d", seq[i]);
    }
    printf("\n");

    for (int i = 1; i <= n; ++i) {
        min_order[i] = n;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (graph[j][i]) {
                min_order[i] = min(min_order[i], min_order[j] + 1);
            }
        }
    }

    printf("%d", min_order[1]);
    for (int i = 2; i <= n; ++i) {
        printf(" %d", min_order[i]);
    }
    printf("\n");

    return 0;
}