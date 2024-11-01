#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int weight;
    int left;
    int right;
} TreeNode;

int dfs(TreeNode* tree, int node, int parent, int* sum) {
    if (node == -1) return 0;
    int leftSum = dfs(tree, tree[node].left, node, sum);
    int rightSum = dfs(tree, tree[node].right, node, sum);
    *sum += leftSum + rightSum;
    return tree[node].weight + leftSum + rightSum;
}

void findMinDistance(TreeNode* tree, int n, int* minDist) {
    for (int i = 0; i < n; i++) {
        int totalDist = 0;
        dfs(tree, i, -1, &totalDist);
        if (i == 0 || totalDist < *minDist) {
            *minDist = totalDist;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    TreeNode* tree = (TreeNode*)malloc(n * sizeof(TreeNode));
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &tree[i].weight, &tree[i].left, &tree[i].right);
    }

    int minDist = INT_MAX;
    findMinDistance(tree, n, &minDist);

    printf("%d\n", minDist);

    free(tree);
    return 0;
}