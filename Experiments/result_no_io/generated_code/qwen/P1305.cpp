#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insertNode(TreeNode** root, char parent, char leftChild, char rightChild) {
    if (*root == NULL) {
        return;
    }
    if ((*root)->data == parent) {
        if (leftChild != '*') {
            (*root)->left = createNode(leftChild);
        }
        if (rightChild != '*') {
            (*root)->right = createNode(rightChild);
        }
    } else {
        insertNode(&(*root)->left, parent, leftChild, rightChild);
        insertNode(&(*root)->right, parent, leftChild, rightChild);
    }
}

void preOrderTraversal(TreeNode* node) {
    if (node != NULL) {
        printf("%c", node->data);
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // Consume the newline character after reading the integer

    TreeNode* root = NULL;
    for (int i = 0; i < n; i++) {
        char parent, leftChild, rightChild;
        scanf(" %c %c %c", &parent, &leftChild, &rightChild);
        if (i == 0) {
            root = createNode(parent);
            insertNode(&root, parent, leftChild, rightChild);
        } else {
            insertNode(&root, parent, leftChild, rightChild);
        }
    }

    preOrderTraversal(root);
    printf("\n");

    return 0;
}