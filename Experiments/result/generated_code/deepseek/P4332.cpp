#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

typedef struct Node {
    int id;
    int input[3];
    int output;
    struct Node* children[3];
} Node;

Node* createNode(int id, int x1, int x2, int x3) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = id;
    node->input[0] = x1;
    node->input[1] = x2;
    node->input[2] = x3;
    node->output = 0;
    node->children[0] = node->children[1] = node->children[2] = NULL;
    return node;
}

void buildTree(Node* nodes[], int n, int inputs[]) {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            if (nodes[i]->input[j] > n) {
                nodes[i]->children[j] = NULL;
                nodes[i]->output += inputs[nodes[i]->input[j] - n - 1];
            } else {
                nodes[i]->children[j] = nodes[nodes[i]->input[j]];
            }
        }
    }
}

void updateTree(Node* node) {
    if (node == NULL) return;
    int count0 = 0, count1 = 0;
    for (int i = 0; i < 3; i++) {
        if (node->children[i] == NULL) continue;
        if (node->children[i]->output == 0) count0++;
        else count1++;
    }
    int newOutput = (count1 > count0) ? 1 : 0;
    if (node->output != newOutput) {
        node->output = newOutput;
        for (int i = 0; i < 3; i++) {
            if (node->children[i] != NULL) {
                updateTree(node->children[i]);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Node* nodes[MAXN];
    for (int i = 1; i <= n; i++) {
        int x1, x2, x3;
        scanf("%d %d %d", &x1, &x2, &x3);
        nodes[i] = createNode(i, x1, x2, x3);
    }

    int inputs[2 * n + 1];
    for (int i = 0; i < 2 * n + 1; i++) {
        scanf("%d", &inputs[i]);
    }

    buildTree(nodes, n, inputs);

    int q;
    scanf("%d", &q);
    while (q--) {
        int x;
        scanf("%d", &x);
        inputs[x - n - 1] = 1 - inputs[x - n - 1];
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 3; j++) {
                if (nodes[i]->input[j] == x) {
                    nodes[i]->output = inputs[x - n - 1];
                    updateTree(nodes[i]);
                    break;
                }
            }
        }
        printf("%d\n", nodes[1]->output);
    }

    for (int i = 1; i <= n; i++) {
        free(nodes[i]);
    }

    return 0;
}