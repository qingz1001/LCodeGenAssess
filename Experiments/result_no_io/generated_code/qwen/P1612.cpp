#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int parent;
    int weight;
    int param;
    int max_chain_length;
} Node;

Node tree[MAXN];

void dfs(int node) {
    if (tree[node].parent == -1) return;

    dfs(tree[node].parent);

    int current_weight = tree[node].weight;
    int current_max_length = 1;

    for (int i = tree[node].parent; i != -1; i = tree[i].parent) {
        current_weight += tree[i].weight;
        if (current_weight > tree[node].param) break;
        current_max_length++;
    }

    tree[node].max_chain_length = current_max_length;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 2; i <= n; i++) {
        scanf("%d", &tree[i].parent);
        tree[tree[i].parent].parent = tree[i].parent - 1; // Adjusting for 0-based indexing
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &tree[i].weight, &tree[i].param);
    }

    for (int i = 1; i <= n; i++) {
        tree[i].parent--;
    }

    dfs(1); // Starting DFS from the root (node 1)

    for (int i = 1; i <= n; i++) {
        printf("%d ", tree[i].max_chain_length);
    }
    printf("\n");

    return 0;
}