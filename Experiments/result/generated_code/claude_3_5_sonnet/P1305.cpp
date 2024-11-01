#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 26

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void preorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%c", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

int main() {
    int n;
    scanf("%d", &n);

    Node* nodes[MAX_NODES] = {NULL};

    for (int i = 0; i < n; i++) {
        char parent, left, right;
        scanf(" %c%c%c", &parent, &left, &right);

        if (nodes[parent - 'a'] == NULL) {
            nodes[parent - 'a'] = createNode(parent);
        }

        if (left != '*') {
            nodes[left - 'a'] = createNode(left);
            nodes[parent - 'a']->left = nodes[left - 'a'];
        }

        if (right != '*') {
            nodes[right - 'a'] = createNode(right);
            nodes[parent - 'a']->right = nodes[right - 'a'];
        }
    }

    preorderTraversal(nodes[0]);
    printf("\n");

    return 0;
}