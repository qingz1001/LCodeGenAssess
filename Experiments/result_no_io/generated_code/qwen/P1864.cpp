#include <stdio.h>
#include <stdlib.h>

#define MAXN 71

typedef struct Node {
    int data, weight, frequency;
    struct Node *left, *right;
} Node;

Node* createNode(int data, int weight, int frequency) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->weight = weight;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insert(Node** root, int data, int weight, int frequency) {
    if (*root == NULL) {
        *root = createNode(data, weight, frequency);
        return;
    }
    if (data < (*root)->data) {
        insert(&(*root)->left, data, weight, frequency);
    } else {
        insert(&(*root)->right, data, weight, frequency);
    }
}

int calculateCost(Node* root, int depth) {
    if (root == NULL) return 0;
    return root->frequency * depth + calculateCost(root->left, depth + 1) + calculateCost(root->right, depth + 1);
}

void modifyWeight(Node** root, int target, int newWeight, int k) {
    if (*root == NULL) return;
    if ((*root)->data == target) {
        int oldWeight = (*root)->weight;
        (*root)->weight = newWeight;
        k -= abs(newWeight - oldWeight);
        if (k < 0) {
            (*root)->weight = oldWeight;
            k += abs(newWeight - oldWeight);
        }
        return;
    }
    if (target < (*root)->data) {
        modifyWeight(&(*root)->left, target, newWeight, k);
    } else {
        modifyWeight(&(*root)->right, target, newWeight, k);
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int data[MAXN], weight[MAXN], frequency[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &data[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &weight[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &frequency[i]);
    }

    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        insert(&root, data[i], weight[i], frequency[i]);
    }

    int minCost = calculateCost(root, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && weight[i] > weight[j]) {
                int temp = weight[i];
                weight[i] = weight[j];
                weight[j] = temp;
                int cost = calculateCost(root, 1);
                if (cost < minCost) {
                    minCost = cost;
                }
                weight[i] = temp;
                weight[j] = temp;
            }
        }
    }

    printf("%d\n", minCost);

    return 0;
}