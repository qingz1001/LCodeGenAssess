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
        tree[val - 'a'] = createNode(val);
    }
    
    for (int i = 0; i < n; i++) {
        char val = nodes[i][0];
        char left = nodes[i][1];
        char right = nodes[i][2];
        
        if (left != '*') {
            tree[val - 'a']->left = tree[left - 'a'];
        }
        if (right != '*') {
            tree[val - 'a']->right = tree[right - 'a'];
        }
    }
    
    return tree[nodes[0][0] - 'a'];
}

void preOrderTraversal(TreeNode* root) {
    if (root == NULL) return;
    printf("%c", root->val);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

int main() {
    int n;
    scanf("%d", &n);
    char nodes[26][3];
    
    for (int i = 0; i < n; i++) {
        scanf(" %c%c%c", &nodes[i][0], &nodes[i][1], &nodes[i][2]);
    }
    
    TreeNode* root = buildTree(n, nodes);
    preOrderTraversal(root);
    printf("\n");
    
    return 0;
}