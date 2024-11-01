#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1005

int N;
int parent[MAX_N];
int level[MAX_N];

void dfs(int node, int current_level) {
    if (level[node] != -1) return; // already visited
    level[node] = current_level;
    for (int i = 2; i <= N; i++) {
        if (parent[i] == node) {
            dfs(i, current_level + 1);
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 2; i <= N; i++) {
        scanf("%d", &parent[i]);
    }

    // Initialize levels to -1 (unvisited)
    for (int i = 1; i <= N; i++) {
        level[i] = -1;
    }

    // Perform DFS starting from the king (node 1)
    dfs(1, 0);

    // Find the maximum level
    int max_time = 0;
    for (int i = 1; i <= N; i++) {
        if (level[i] > max_time) {
            max_time = level[i];
        }
    }

    printf("%d\n", max_time);

    // Find all nodes that can be chosen to minimize the time
    printf("1 ");
    for (int i = 2; i <= N; i++) {
        if (level[parent[i]] == level[i] - 1) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}