#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char type;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* createNode(char type) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->type = type;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void postorderTraversal(TreeNode* root, char* result, int* index) {
    if (root == NULL) return;
    postorderTraversal(root->left, result, index);
    postorderTraversal(root->right, result, index);
    result[(*index)++] = root->type;
}

TreeNode* buildTree(char* s, int start, int end) {
    if (start > end) return NULL;
    if (start == end) {
        if (s[start] == '0') return createNode('B');
        else return createNode('I');
    }
    int mid = (start + end) / 2;
    TreeNode* root = createNode(s[mid]);
    root->left = buildTree(s, start, mid - 1);
    root->right = buildTree(s, mid + 1, end);
    return root;
}

int main() {
    int N;
    scanf("%d", &N);
    int length = 1 << N;
    char S[length];
    scanf("%s", S);

    TreeNode* root = buildTree(S, 0, length - 1);
    char result[length];
    int index = 0;
    postorderTraversal(root, result, &index);
    for (int i = 0; i < index; i++) {
        printf("%c", result[i]);
    }
    printf("\n");

    // Free the allocated memory
    freeTree(root);
    return 0;
}

void freeTree(TreeNode* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}