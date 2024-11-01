#include <stdio.h>
#include <stdlib.h>

#define MAXN 150

int n, p;
int parent[MAXN + 1];
int subtree_size[MAXN + 1];

void dfs(int node) {
    subtree_size[node] = 1;
    for (int i = 1; i <= n; i++) {
        if (parent[i] == node) {
            dfs(i);
            subtree_size[node] += subtree_size[i];
        }
    }
}

int find_min_edges_to_separate(int target_size) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (subtree_size[i] == target_size && parent[i] != 0) {
            count++;
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &n, &p);

    for (int i = 2; i <= n; i++) {
        scanf("%d %d", &parent[i], &i);
    }

    dfs(1);
    int result = find_min_edges_to_separate(p);
    printf("%d\n", result);

    return 0;
}