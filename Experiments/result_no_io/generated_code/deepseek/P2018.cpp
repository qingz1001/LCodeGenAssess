#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int n;
int parent[MAXN + 1];
int depth[MAXN + 1];
int max_depth = 0;

void dfs(int node, int d) {
    depth[node] = d;
    if (d > max_depth) {
        max_depth = d;
    }
    if (parent[node] != 0) {
        dfs(parent[node], d + 1);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &parent[i]);
    }

    // Calculate the depth of each node
    for (int i = 1; i <= n; i++) {
        dfs(i, 0);
    }

    // Output the maximum depth
    printf("%d\n", max_depth);

    // Find and output the nodes that can be chosen to minimize the time
    for (int i = 1; i <= n; i++) {
        if (depth[i] == max_depth) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}