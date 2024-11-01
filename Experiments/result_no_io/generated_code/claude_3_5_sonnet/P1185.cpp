#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_M 10
#define MAX_WIDTH 1024

char tree[MAX_M][MAX_WIDTH];
int m, n;

void init_tree() {
    for (int i = 0; i < m; i++) {
        memset(tree[i], ' ', sizeof(tree[i]));
    }
}

void draw_full_tree(int row, int col, int level) {
    if (level > m) return;

    tree[row][col] = 'o';

    if (level < m) {
        tree[row + 1][col - 1] = '/';
        tree[row + 1][col + 1] = '\\';
        
        int offset = 1 << (m - level - 1);
        draw_full_tree(row + 2, col - offset, level + 1);
        draw_full_tree(row + 2, col + offset, level + 1);
    }
}

void remove_node(int level, int pos) {
    int row = 2 * (level - 1);
    int col = (1 << (m - 1)) - 1 + (pos - 1) * (1 << (m - level + 1));

    if (level == m) {
        tree[row][col] = ' ';
    } else {
        tree[row][col] = ' ';
        tree[row + 1][col - 1] = ' ';
        tree[row + 1][col + 1] = ' ';
        
        int offset = 1 << (m - level - 1);
        remove_node(level + 1, 2 * pos - 1);
        remove_node(level + 1, 2 * pos);
    }
}

void print_tree() {
    for (int i = 0; i < 2 * m - 1; i++) {
        int j = MAX_WIDTH - 1;
        while (j >= 0 && tree[i][j] == ' ') j--;
        tree[i][j + 1] = '\0';
        printf("%s\n", tree[i]);
    }
}

int main() {
    scanf("%d %d", &m, &n);

    init_tree();
    draw_full_tree(0, (1 << (m - 1)) - 1, 1);

    for (int i = 0; i < n; i++) {
        int level, pos;
        scanf("%d %d", &level, &pos);
        remove_node(level, pos);
    }

    print_tree();

    return 0;
}