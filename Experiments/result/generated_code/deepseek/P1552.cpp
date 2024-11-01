#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef struct {
    int parent, cost, leadership;
} Ninja;

Ninja ninjas[MAXN];
int N, M;

typedef struct Node {
    int cost, count;
    struct Node *left, *right;
} Node;

Node *newNode(int cost) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->cost = cost;
    node->count = 1;
    node->left = node->right = NULL;
    return node;
}

Node *insert(Node *root, int cost) {
    if (root == NULL) return newNode(cost);
    if (cost < root->cost) root->left = insert(root->left, cost);
    else if (cost > root->cost) root->right = insert(root->right, cost);
    else root->count++;
    return root;
}

int countLessThan(Node *root, int maxCost) {
    if (root == NULL) return 0;
    if (root->cost <= maxCost) {
        return root->count + countLessThan(root->left, maxCost) + countLessThan(root->right, maxCost);
    } else {
        return countLessThan(root->left, maxCost);
    }
}

void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int dfs(int idx, Node *root) {
    root = insert(root, ninjas[idx].cost);
    int totalCost = countLessThan(root, M);
    int maxSatisfaction = totalCost * ninjas[idx].leadership;

    for (int i = 1; i <= N; i++) {
        if (ninjas[i].parent == idx) {
            int childSatisfaction = dfs(i, root);
            if (childSatisfaction > maxSatisfaction) {
                maxSatisfaction = childSatisfaction;
            }
        }
    }

    return maxSatisfaction;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d %d %d", &ninjas[i].parent, &ninjas[i].cost, &ninjas[i].leadership);
    }

    Node *root = NULL;
    int maxSatisfaction = dfs(0, root);
    freeTree(root);

    printf("%d\n", maxSatisfaction);
    return 0;
}