#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode {
    char val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* build(char* inorder, int in_start, int in_end, char* postorder, int post_start, int post_end) {
    if (in_start > in_end || post_start > post_end) return NULL;
    char root_val = postorder[post_end];
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = root_val;
    root->left = root->right = NULL;
    int in_root = in_start;
    while (in_root <= in_end && inorder[in_root] != root_val) in_root++;
    int left_size = in_root - in_start;
    root->left = build(inorder, in_start, in_root -1, postorder, post_start, post_start + left_size -1);
    root->right = build(inorder, in_root +1, in_end, postorder, post_start + left_size, post_end -1);
    return root;
}

void preorder(TreeNode* root, char* output, int* index) {
    if (root == NULL) return;
    output[(*index)++] = root->val;
    preorder(root->left, output, index);
    preorder(root->right, output, index);
}

int main(){
    char inorder[9], postorder[9];
    scanf("%s %s", inorder, postorder);
    int n = strlen(inorder);
    TreeNode* root = build(inorder, 0, n-1, postorder, 0, n-1);
    char output[9];
    int idx =0;
    preorder(root, output, &idx);
    output[idx] = '\0';
    printf("%s", output);
    return 0;
}