#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

void printTree(char tree[MAX_SIZE][MAX_SIZE], int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height * 4 - 1; j++) {
            printf("%c", tree[i][j]);
        }
        printf("\n");
    }
}

void drawBinaryTree(int m, char tree[MAX_SIZE][MAX_SIZE]) {
    int width = m * 4 - 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < width; j++) {
            tree[i][j] = ' ';
        }
    }

    int level = 0;
    int index = 0;
    while (level < m) {
        int num_nodes = 1 << level;
        int offset = (width - num_nodes * 3) / 2;
        for (int i = 0; i < num_nodes; i++) {
            if ((index & 1) == 0) {
                tree[level + 1][offset + i * 3] = '/';
            } else {
                tree[level + 1][offset + i * 3] = '\\';
            }
            index++;
        }
        level++;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < width; j++) {
            if (tree[i][j] == '/' || tree[i][j] == '\\') {
                if (i > 0 && (tree[i - 1][j - 1] == ' ' || tree[i - 1][j + 1] == ' ')) {
                    tree[i][j] = ' ';
                }
            }
        }
    }
}

void deleteNodes(int m, int n, int nodes[MAX_SIZE][2], char tree[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < n; i++) {
        int level = nodes[i][0];
        int pos = nodes[i][1];
        int width = m * 4 - 1;
        int offset = (width - (1 << (level - 1)) * 3) / 2;
        int node_index = (pos - 1) * 2 + 1;

        int left_offset = offset + node_index * 3 - 1;
        int right_offset = offset + node_index * 3 + 1;

        tree[level][left_offset] = ' ';
        tree[level][right_offset] = ' ';
        tree[level + 1][left_offset] = ' ';
        tree[level + 1][right_offset] = ' ';
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    char tree[MAX_SIZE][MAX_SIZE];
    drawBinaryTree(m, tree);
    printTree(tree, m);

    if (n > 0) {
        int nodes[MAX_SIZE][2];
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &nodes[i][0], &nodes[i][1]);
        }
        deleteNodes(m, n, nodes, tree);
        printTree(tree, m);
    }

    return 0;
}