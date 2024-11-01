#include <stdio.h>
#include <stdlib.h>

#define MAX_DEPTH 10
#define MAX_NODES (1 << MAX_DEPTH)

struct Node {
    int left;
    int right;
    int parent;
};

struct Node tree[MAX_NODES];
int deleted[MAX_NODES];

void buildTree(int depth) {
    int totalNodes = (1 << depth) - 1;
    for (int i = 0; i < totalNodes; i++) {
        tree[i].left = 2 * i + 1;
        tree[i].right = 2 * i + 2;
        tree[i].parent = (i - 1) / 2;
    }
}

void deleteNode(int depth, int index) {
    deleted[index] = 1;
    if (tree[index].left < MAX_NODES) deleteNode(depth - 1, tree[index].left);
    if (tree[index].right < MAX_NODES) deleteNode(depth - 1, tree[index].right);
}

void printTree(int depth, int index, int indent) {
    if (deleted[index]) return;
    for (int i = 0; i < indent; i++) printf(" ");
    printf("o\n");
    if (depth > 1) {
        if (tree[index].left < MAX_NODES) {
            for (int i = 0; i < indent; i++) printf(" ");
            printf("/\n");
            printTree(depth - 1, tree[index].left, indent + 2);
        }
        if (tree[index].right < MAX_NODES) {
            for (int i = 0; i < indent; i++) printf(" ");
            printf("\\\n");
            printTree(depth - 1, tree[index].right, indent + 2);
        }
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    buildTree(m);
    for (int i = 0; i < n; i++) {
        int depth, index;
        scanf("%d %d", &depth, &index);
        int actualIndex = (1 << (depth - 1)) + index - 1;
        deleteNode(m, actualIndex);
    }
    printTree(m, 0, 0);
    return 0;
}