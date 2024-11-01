#include <stdio.h>
#include <string.h>

#define MAX_M 10
#define MAX_SIZE 2048

char tree[MAX_SIZE][MAX_SIZE];
int m, n;

void init_tree() {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            tree[i][j] = ' ';
        }
    }
}

void draw_tree(int row, int col, int level) {
    if (level > m) return;

    tree[row][col] = 'o';
    if (level == m) return;

    tree[row + 1][col - 1] = '/';
    tree[row + 1][col + 1] = '\\';

    int offset = 1 << (m - level - 1);
    draw_tree(row + 2, col - offset, level + 1);
    draw_tree(row + 2, col + offset, level + 1);
}

void remove_node(int level, int pos) {
    int row = 2 * (level - 1);
    int col = (1 << (m - 1)) + (pos - 1) * (1 << (m - level));
    tree[row][col] = ' ';
    if (level < m) {
        tree[row + 1][col - 1] = ' ';
        tree[row + 1][col + 1] = ' ';
    }
}

void print_tree() {
    int max_width = (1 << m) - 1;
    for (int i = 0; i < 2 * m - 1; i++) {
        int printed = 0;
        for (int j = 0; j < max_width; j++) {
            if (tree[i][j] != ' ' || printed) {
                putchar(tree[i][j]);
                printed = 1;
            }
        }
        if (printed) putchar('\n');
    }
}

int main() {
    scanf("%d %d", &m, &n);

    init_tree();
    draw_tree(0, (1 << (m - 1)) - 1, 1);

    for (int i = 0; i < n; i++) {
        int level, pos;
        scanf("%d %d", &level, &pos);
        remove_node(level, pos);
    }

    print_tree();
    return 0;
}