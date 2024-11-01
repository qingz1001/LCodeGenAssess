#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int weight;
    int left;
    int right;
} TreeNode;

int minDistance = INT_MAX;

void dfs(TreeNode* tree, int index, int distance) {
    if (tree[index].left == -1 && tree[index].right == -1) {
        if (distance < minDistance) {
            minDistance = distance;
        }
        return;
    }

    if (tree[index].left != -1) {
        dfs(tree, tree[index].left, distance + abs(index - tree[index].left));
    }

    if (tree[index].right != -1) {
        dfs(tree, tree[index].right, distance + abs(index - tree[index].right));
    }
}

int main() {
    int n;
    scanf("%d", &n);

    TreeNode* tree = (TreeNode*)malloc(n * sizeof(TreeNode));

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &tree[i].weight, &tree[i].left, &tree[i].right);
        if (tree[i].left != 0) tree[i].left--;
        if (tree[i].right != 0) tree[i].right--;
    }

    for (int i = 0; i < n; i++) {
        dfs(tree, i, 0);
    }

    printf("%d\n", minDistance);

    free(tree);
    return 0;
}