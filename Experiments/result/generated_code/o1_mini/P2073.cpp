#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Treap node definition
typedef struct Node {
    int C;
    int W;
    int priority;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* createNode(int C, int W) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->C = C;
    node->W = W;
    node->priority = rand();
    node->left = node->right = NULL;
    return node;
}

// Split treap into two treaps: left has keys < C, right has keys >= C
void split(Node* root, int C, Node** left, Node** right) {
    if (!root) {
        *left = *right = NULL;
    }
    else if (C > root->C) {
        split(root->right, C, &(root->right), right);
        *left = root;
    }
    else {
        split(root->left, C, left, &(root->left));
        *right = root;
    }
}

// Merge two treaps
Node* merge(Node* left, Node* right) {
    if (!left || !right)
        return left ? left : right;
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        return right;
    }
}

// Insert a node into treap
Node* insert(Node* root, Node* node) {
    if (!root)
        return node;
    if (node->C == root->C)
        return root;
    if (node->priority > root->priority) {
        split(root, node->C, &(node->left), &(node->right));
        return node;
    }
    else if (node->C < root->C) {
        root->left = insert(root->left, node);
    }
    else {
        root->right = insert(root->right, node);
    }
    return root;
}

// Find the node with key C
Node* find(Node* root, int C) {
    while (root) {
        if (C == root->C)
            return root;
        else if (C < root->C)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

// Delete a node with key C
Node* deleteNode(Node* root, int C) {
    if (!root)
        return NULL;
    if (C < root->C) {
        root->left = deleteNode(root->left, C);
    }
    else if (C > root->C) {
        root->right = deleteNode(root->right, C);
    }
    else {
        Node* temp = merge(root->left, root->right);
        free(root);
        return temp;
    }
    return root;
}

// Find the node with minimum C
Node* findMin(Node* root) {
    if (!root)
        return NULL;
    while (root->left)
        root = root->left;
    return root;
}

// Find the node with maximum C
Node* findMax(Node* root) {
    if (!root)
        return NULL;
    while (root->right)
        root = root->right;
    return root;
}

int main(){
    srand(time(NULL));
    char line[50];
    Node* root = NULL;
    long long total_W = 0;
    long long total_C = 0;
    while (fgets(line, sizeof(line), stdin)) {
        int op;
        if (sscanf(line, "%d", &op) != 1)
            continue;
        if (op == -1)
            break;
        if (op == 1) {
            int W, C;
            if (sscanf(line, "%*d %d %d", &W, &C) != 2)
                continue;
            if (!find(root, C)) {
                Node* node = createNode(C, W);
                root = insert(root, node);
                total_W += W;
                total_C += C;
            }
        }
        else if (op == 2) {
            if (root) {
                Node* maxNode = findMax(root);
                if (maxNode) {
                    total_W -= maxNode->W;
                    total_C -= maxNode->C;
                    root = deleteNode(root, maxNode->C);
                }
            }
        }
        else if (op == 3) {
            if (root) {
                Node* minNode = findMin(root);
                if (minNode) {
                    total_W -= minNode->W;
                    total_C -= minNode->C;
                    root = deleteNode(root, minNode->C);
                }
            }
        }
    }
    printf("%lld %lld\n", total_W, total_C);
    return 0;
}