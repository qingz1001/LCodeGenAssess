#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, h, isStart;
} Node;

int cmp(const void *a, const void *b) {
    Node *na = (Node *)a;
    Node *nb = (Node *)b;
    if (na->x != nb->x) return na->x - nb->x;
    if (na->isStart != nb->isStart) return na->isStart - nb->isStart;
    return nb->h - na->h;
}

int main() {
    int n;
    scanf("%d", &n);
    Node *nodes = (Node *)malloc(2 * n * sizeof(Node));
    int nodeCount = 0;

    for (int i = 0; i < n; i++) {
        int h, l, r;
        scanf("%d%d%d", &h, &l, &r);
        nodes[nodeCount++] = (Node){l, h, 1};
        nodes[nodeCount++] = (Node){r, h, 0};
    }

    qsort(nodes, nodeCount, sizeof(Node), cmp);

    int m = 0, lastHeight = 0;
    Node *output = (Node *)malloc(nodeCount * sizeof(Node));
    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i].isStart) {
            if (nodes[i].h > lastHeight) {
                output[m++] = nodes[i];
            }
        } else {
            if (nodes[i].h > lastHeight) {
                output[m++] = nodes[i];
            } else if (nodes[i].h < lastHeight) {
                output[m++] = nodes[i];
            }
        }
        lastHeight = nodes[i].h;
    }

    printf("%d\n", m);
    for (int i = 0; i < m; i++) {
        printf("%d %d\n", output[i].x, output[i].h);
    }

    free(nodes);
    free(output);
    return 0;
}