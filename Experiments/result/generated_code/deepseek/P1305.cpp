#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(char val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* buildTree(int n, char nodes[][3]) {
    TreeNode* tree[26] = {NULL};
    for (int i = 0; i < n; i++) {
        char val = nodes[i][0];
        if (tree[val - 'a'] == NULL) {
            tree[val - 'a'] = createNode(val);
        }
        if (nodes[i][1] != '*') {
            tree[nodes[i][1] - 'a'] = createNode(nodes[i][1]);
            tree[val - 'a']->left = tree[nodes[i][1] - 'a'];
        }
        if (nodes[i][2] != '*') {
            tree[nodes[i][2] - 'a'] = createNode(nodes[i][2]);
            tree[val - 'a']->right = tree[nodes[i][2] - 'a'];
        }
    }
    return tree[nodes[0][0] - 'a'];
}

void preOrder(TreeNode* root) {
    if (root == NULL) return;
    printf("%c", root->val);
    preOrder(root->left);
    preOrder(root->right);
}

int main() {
    int n;
    scanf("%d", &n);
    char nodes[n][3];
    for (int i = 0; i < n; i++) {
        scanf("%s", nodes[i]);
    }
    TreeNode* root = buildTree(n, nodes);
    preOrder(root);
    printf("\n");
    return 0;
}