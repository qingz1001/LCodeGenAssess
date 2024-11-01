#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1001

int n;
int tree[MAXN][2]; // tree[i][0] is the left child, tree[i][1] is the right child
int depth[MAXN];

void dfs(int node) {
    if (tree[node][0] != -1) {
        dfs(tree[node][0]);
        depth[node] = depth[tree[node][0]] + 1;
    }
    if (tree[node][1] != -1) {
        dfs(tree[node][1]);
        depth[node] = depth[tree[node][1]] + 1;
    }
}

int main() {
    scanf("%d", &n);
    memset(tree, -1, sizeof(tree));
    memset(depth, 0, sizeof(depth));
    
    for (int i = 2; i <= n; i++) {
        int parent;
        scanf("%d", &parent);
        if (tree[parent][0] == -1) {
            tree[parent][0] = i;
        } else {
            tree[parent][1] = i;
        }
    }
    
    dfs(1); // start from the root node which is 1
    
    int max_depth = 0;
    for (int i = 1; i <= n; i++) {
        if (tree[i][0] == -1 && tree[i][1] == -1) { // leaf nodes
            max_depth = max_depth > depth[i] ? max_depth : depth[i];
        }
    }
    
    printf("%d\n", max_depth);
    
    for (int i = 1; i <= n; i++) {
        if (tree[i][0] == -1 && tree[i][1] == -1) { // leaf nodes
            printf("%d ", i);
        }
    }
    printf("\n");
    
    return 0;
}