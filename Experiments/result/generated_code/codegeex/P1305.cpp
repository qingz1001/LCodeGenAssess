#include <stdio.h>
#include <string.h>

#define MAX_NODE 26

typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode nodes[MAX_NODE];
int nodeCount = 0;

TreeNode* createNode(char data) {
    TreeNode *newNode = &nodes[nodeCount++];
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void buildTree(TreeNode *root, char leftChild, char rightChild) {
    if (leftChild != '*') {
        root->left = createNode(leftChild);
    }
    if (rightChild != '*') {
        root->right = createNode(rightChild);
    }
}

void preOrderTraversal(TreeNode *root) {
    if (root == NULL) return;
    printf("%c", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

int main() {
    int n;
    scanf("%d", &n);
    char rootChar;
    scanf("%c", &rootChar); // consume newline character
    scanf("%c", &rootChar); // read the root character
    TreeNode *root = createNode(rootChar);

    for (int i = 0; i < n - 1; i++) {
        char line[4];
        scanf("%s", line);
        char parent = line[0];
        char leftChild = line[1];
        char rightChild = line[2];

        TreeNode *parentNode = NULL;
        for (int j = 0; j < nodeCount; j++) {
            if (nodes[j].data == parent) {
                parentNode = &nodes[j];
                break;
            }
        }
        if (parentNode == NULL) {
            parentNode = createNode(parent);
        }
        buildTree(parentNode, leftChild, rightChild);
    }

    preOrderTraversal(root);
    printf("\n");
    return 0;
}