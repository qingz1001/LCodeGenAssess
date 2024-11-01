#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode nodes[26];

TreeNode* getNode(char c) {
    if (c == '*') return NULL;
    return &nodes[c - 'A'];
}

void preorder(TreeNode* root) {
    if (root == NULL) return;
    printf("%c", root->val);
    preorder(root->left);
    preorder(root->right);
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<26;i++){
        nodes[i].val = 'A' + i;
        nodes[i].left = NULL;
        nodes[i].right = NULL;
    }
    char parent, left, right;
    for(int i=0;i<n;i++){
        scanf(" %c %c %c", &parent, &left, &right);
        TreeNode* current = getNode(parent);
        current->left = getNode(left);
        current->right = getNode(right);
    }
    TreeNode* root = &nodes[0];
    preorder(root);
    return 0;
}