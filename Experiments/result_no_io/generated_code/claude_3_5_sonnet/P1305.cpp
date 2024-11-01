#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 26

typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void preorderTraversal(Node* root) {
    if (root == NULL) return;
    printf("%c", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

int main() {
    int n;
    scanf("%d", &n);

    Node* nodes[MAX_NODES] = {NULL};
    char root, left, right;

    for (int i = 0; i < n; i++) {
        scanf(" %c %c %c", &root, &left, &right);
        
        if (nodes[root - 'A'] == NULL) {
            nodes[root - 'A'] = createNode(root);
        }
        
        if (left != '*') {
            nodes[left - 'A'] = createNode(left);
            nodes[root - 'A']->left = nodes[left - 'A'];
        }
        
        if (right != '*') {
            nodes[right - 'A'] = createNode(right);
            nodes[root - 'A']->right = nodes[right - 'A'];
        }
    }

    preorderTraversal(nodes[0]);
    printf("\n");

    return 0;
}