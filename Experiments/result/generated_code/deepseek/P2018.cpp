#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000

typedef struct Node {
    int id;
    struct Node* parent;
    struct Node* child;
    struct Node* next;
} Node;

Node* createNode(int id) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->next = NULL;
    return newNode;
}

void addChild(Node* parent, Node* child) {
    if (parent->child == NULL) {
        parent->child = child;
    } else {
        Node* temp = parent->child;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = child;
    }
    child->parent = parent;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(Node* node, int depth, int* maxDepth) {
    if (node == NULL) return depth - 1;
    int currentMaxDepth = depth;
    Node* temp = node->child;
    while (temp != NULL) {
        currentMaxDepth = max(currentMaxDepth, dfs(temp, depth + 1, maxDepth));
        temp = temp->next;
    }
    if (currentMaxDepth == *maxDepth) {
        printf("%d ", node->id);
    }
    return currentMaxDepth;
}

int main() {
    int N;
    scanf("%d", &N);

    Node* nodes[MAXN + 1];
    for (int i = 1; i <= N; i++) {
        nodes[i] = createNode(i);
    }

    for (int i = 2; i <= N; i++) {
        int parentId;
        scanf("%d", &parentId);
        addChild(nodes[parentId], nodes[i]);
    }

    int maxDepth = 0;
    int totalTime = dfs(nodes[1], 0, &maxDepth);
    printf("\n%d\n", totalTime);

    for (int i = 1; i <= N; i++) {
        free(nodes[i]);
    }

    return 0;
}