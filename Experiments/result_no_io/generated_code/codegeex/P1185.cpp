#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEIGHT 10

int tree[MAX_HEIGHT][1 << MAX_HEIGHT];

void drawTree(int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", tree[i][j]);
        }
        printf("\n");
    }
}

void buildTree(int height, int width) {
    if (height == 0) return;

    int mid = width / 2;
    tree[height - 1][mid] = 'o';

    if (height > 1) {
        tree[height - 1][mid - 1] = '/';
        tree[height - 1][mid + 1] = '\\';

        buildTree(height - 1, mid);
        buildTree(height - 1, width - mid);
    }
}

void removeNodes(int height, int n, int *nodes) {
    for (int i = 0; i < n; i++) {
        int layer = nodes[2 * i] - 1;
        int index = (1 << (layer - 1)) + nodes[2 * i + 1] - 1;

        tree[layer][index] = ' ';
        if (index > 0 && tree[layer][index - 1] == '/') tree[layer][index - 1] = ' ';
        if (index < width - 1 && tree[layer][index + 1] == '\\') tree[layer][index + 1] = ' ';
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    memset(tree, ' ', sizeof(tree));

    int width = 1 << (m - 1);
    buildTree(m, width);

    int *nodes = (int *)malloc(n * 2 * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &nodes[2 * i], &nodes[2 * i + 1]);
    }

    removeNodes(m, n, nodes);

    drawTree(m, width);

    free(nodes);

    return 0;
}