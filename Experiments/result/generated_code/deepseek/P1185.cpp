#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 10
#define MAX_N 1024

char tree[MAX_M * 2][MAX_N];

void initialize_tree(int m) {
    int width = 1 << (m - 1);
    for (int i = 0; i < m * 2 - 1; i++) {
        for (int j = 0; j < width; j++) {
            tree[i][j] = ' ';
        }
        tree[i][width] = '\0';
    }
}

void draw_full_tree(int m, int row, int col) {
    if (m == 1) {
        tree[row][col] = 'o';
        return;
    }

    int width = 1 << (m - 2);
    tree[row][col] = 'o';
    tree[row + 1][col - 1] = '/';
    tree[row + 1][col + 1] = '\\';

    draw_full_tree(m - 1, row + 2, col - width);
    draw_full_tree(m - 1, row + 2, col + width);
}

void remove_node(int m, int row, int col) {
    if (row >= m * 2 - 1) return;

    tree[row][col] = ' ';
    if (row + 1 < m * 2 - 1) {
        if (tree[row + 1][col - 1] == '/') {
            remove_node(m, row + 2, col - (1 << (m - row / 2 - 2)));
        }
        if (tree[row + 1][col + 1] == '\\') {
            remove_node(m, row + 2, col + (1 << (m - row / 2 - 2)));
        }
        tree[row + 1][col - 1] = ' ';
        tree[row + 1][col + 1] = ' ';
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    initialize_tree(m);
    draw_full_tree(m, 0, (1 << (m - 1)) - 1);

    for (int i = 0; i < n; i++) {
        int row, col;
        scanf("%d %d", &row, &col);
        remove_node(m, (row - 1) * 2, (1 << (row - 1)) - 1 + (col - 1) * 3);
    }

    for (int i = 0; i < m * 2 - 1; i++) {
        printf("%s\n", tree[i]);
    }

    return 0;
}