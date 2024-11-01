#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int N;
int parent[MAX_N + 1];
int depth[MAX_N + 1];
int max_depth = 0;

void dfs(int node, int current_depth) {
    if (current_depth > max_depth) {
        max_depth = current_depth;
    }
    for (int i = 1; i <= N; i++) {
        if (parent[i] == node) {
            dfs(i, current_depth + 1);
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 2; i <= N; i++) {
        scanf("%d", &parent[i]);
    }

    // Find the root (king)
    int root = 1;
    while (parent[root] != 0) {
        root = parent[root];
    }

    // Calculate the maximum depth of the tree
    dfs(root, 0);

    printf("%d\n", max_depth);

    // Find all nodes that can be chosen to minimize the message passing time
    for (int i = 1; i <= N; i++) {
        if (depth[i] == max_depth - 1) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}