#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int n;
int graph[MAX_N][MAX_N];
int visited[MAX_N];
int group[MAX_N];

void dfs(int u, int g) {
    if (visited[u]) return;
    visited[u] = 1;
    group[u] = g;
    for (int v = 1; v <= n; v++) {
        if (graph[u][v]) {
            dfs(v, g);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        while (1) {
            int v;
            scanf("%d", &v);
            if (v == 0) break;
            graph[i][v] = 1;
        }
    }

    int groups = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            groups++;
            dfs(i, groups);
        }
    }

    if (groups != 2) {
        printf("No solution\n");
        return 0;
    }

    int count[2] = {0};
    for (int i = 1; i <= n; i++) {
        count[group[i] - 1]++;
    }

    int diff = abs(count[0] - count[1]);
    if (diff > 1) {
        printf("No solution\n");
        return 0;
    }

    printf("%d ", count[0]);
    for (int i = 1; i <= n; i++) {
        if (group[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");

    printf("%d ", count[1]);
    for (int i = 1; i <= n; i++) {
        if (group[i] == 2) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}