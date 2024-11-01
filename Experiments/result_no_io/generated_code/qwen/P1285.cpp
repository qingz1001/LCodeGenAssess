#include <stdio.h>
#include <stdlib.h>

#define MAX_N 105

int n;
int graph[MAX_N][MAX_N];
int visited[MAX_N];
int group[MAX_N];

void dfs(int node, int g) {
    if (visited[node]) return;
    visited[node] = 1;
    group[node] = g;
    for (int i = 1; i <= n; ++i) {
        if (graph[node][i]) {
            dfs(i, g);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x;
        while (scanf("%d", &x) && x != 0) {
            graph[i][x] = 1;
        }
    }

    int g1_count = 0, g2_count = 0;
    int g1[100], g2[100];

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i, 1);
            g1[g1_count++] = i;
        } else if (group[i] == 1) {
            g1[g1_count++] = i;
        } else {
            g2[g2_count++] = i;
        }
    }

    if (g1_count == 0 || g2_count == 0) {
        printf("No solution\n");
        return 0;
    }

    // Sort the groups in ascending order
    qsort(g1, g1_count, sizeof(int), (int (*)(const void *, const void *))compare);
    qsort(g2, g2_count, sizeof(int), (int (*)(const void *, const void *))compare);

    printf("%d ", g1_count);
    for (int i = 0; i < g1_count; ++i) {
        printf("%d ", g1[i]);
    }
    printf("\n");

    printf("%d ", g2_count);
    for (int i = 0; i < g2_count; ++i) {
        printf("%d ", g2[i]);
    }
    printf("\n");

    return 0;
}