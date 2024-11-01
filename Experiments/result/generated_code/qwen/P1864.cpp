#include <stdio.h>
#include <stdlib.h>

#define MAXN 71

typedef struct Node {
    int data, weight, freq;
    struct Node *left, *right;
} Node;

Node* newNode(int data, int weight, int freq) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->weight = weight;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

Node* insert(Node* root, int data, int weight, int freq) {
    if (root == NULL) return newNode(data, weight, freq);
    if (data < root->data) root->left = insert(root->left, data, weight, freq);
    else root->right = insert(root->right, data, weight, freq);
    return root;
}

int getDepth(Node* node, int depth) {
    if (node == NULL) return 0;
    return depth + getDepth(node->left, depth + 1);
}

long long calculateCost(Node* root, int depth) {
    if (root == NULL) return 0;
    return (long long)root->weight * root->freq * depth + 
           calculateCost(root->left, depth + 1) + 
           calculateCost(root->right, depth + 1);
}

void modifyWeight(Node** root, int target, int newWeight) {
    if (*root == NULL) return;
    if ((*root)->data == target) {
        (*root)->weight = newWeight;
    } else if ((*root)->data > target) {
        modifyWeight(&(*root)->left, target, newWeight);
    } else {
        modifyWeight(&(*root)->right, target, newWeight);
    }
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    int data[MAXN], weight[MAXN], freq[MAXN];
    for (int i = 0; i < N; i++) scanf("%d", &data[i]);
    for (int i = 0; i < N; i++) scanf("%d", &weight[i]);
    for (int i = 0; i < N; i++) scanf("%d", &freq[i]);

    Node* root = NULL;
    for (int i = 0; i < N; i++) {
        root = insert(root, data[i], weight[i], freq[i]);
    }

    long long minCost = calculateCost(root, 1);
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (data[i] != data[j]) {
                modifyWeight(&root, data[i], weight[j]);
                long long cost = calculateCost(root, 1) + K;
                if (cost < minCost) minCost = cost;
                modifyWeight(&root, data[j], weight[i]);
            }
        }
    }

    printf("%lld\n", minCost);
    return 0;
}