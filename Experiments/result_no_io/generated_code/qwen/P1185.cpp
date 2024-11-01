#include <stdio.h>
#include <stdlib.h>

#define MAX_HEIGHT 10

void print_tree(char tree[MAX_HEIGHT][MAX_HEIGHT * 2], int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < MAX_HEIGHT * 2 - 1; j++) {
            printf("%c", tree[i][j]);
        }
        printf("\n");
    }
}

void draw_tree(char tree[MAX_HEIGHT][MAX_HEIGHT * 2], int height) {
    if (height == 0) return;
    int width = (1 << height) - 1;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tree[i][j] = ' ';
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= i; j++) {
            if (tree[i][2 * j + width / (1 << (i + 1))] != ' ') continue;
            if ((i & 1) == 0) {
                tree[i][2 * j + width / (1 << (i + 1))] = '/';
                tree[i + 1][2 * j + width / (1 << i)] = 'o';
                tree[i + 1][2 * j + width / (1 << i) + 1] = '\\';
            } else {
                tree[i][2 * j + width / (1 << (i + 1))] = '\\';
                tree[i + 1][2 * j + width / (1 << i) - 1] = 'o';
                tree[i + 1][2 * j + width / (1 << i)] = '/';
            }
        }
    }
}

void delete_node(char tree[MAX_HEIGHT][MAX_HEIGHT * 2], int level, int pos) {
    int width = (1 << level) - 1;
    int index = 2 * pos - 1;
    while (index < width) {
        tree[level][index] = ' ';
        index += 2;
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    char tree[MAX_HEIGHT][MAX_HEIGHT * 2];
    draw_tree(tree, m);
    for (int i = 0; i < n; i++) {
        int level, pos;
        scanf("%d %d", &level, &pos);
        delete_node(tree, level, pos);
    }
    print_tree(tree, m);
    return 0;
}