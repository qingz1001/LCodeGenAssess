#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

int n;
int graph[MAXN][2];
int visited[MAXN];

void dfs(int node, int parent, int steps[], int step_index) {
    if (visited[node]) return;
    visited[node] = 1;
    steps[step_index++] = node;

    if (node == n) {
        printf("%d\n", step_index);
        for (int i = 0; i < step_index; i++) {
            printf("%d\n", steps[i]);
        }
        exit(0);
    }

    for (int i = 0; i < 2; i++) {
        int neighbor = graph[node][i];
        if (neighbor != parent && abs(node - neighbor) <= 2) {
            dfs(neighbor, node, steps, step_index);
        }
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u-1][0] = v-1;
        graph[v-1][0] = u-1;
    }

    int steps[MAXN];
    dfs(0, -1, steps, 0);

    printf("BRAK\n");
    return 0;
}