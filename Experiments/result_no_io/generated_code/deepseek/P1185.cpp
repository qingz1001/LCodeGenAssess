#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEIGHT 10
#define MAX_WIDTH 1024

char tree[MAX_HEIGHT][MAX_WIDTH];

void initialize_tree(int m) {
    int width = 1 << (m - 1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < width; j++) {
            tree[i][j] = ' ';
        }
        tree[i][width] = '\0';
    }
}

void draw_full_tree(int m) {
    int width = 1 << (m - 1);
    int mid = width / 2;

    for (int i = 0; i < m; i++) {
        int nodes = 1 << i;
        int gap = width / nodes;
        for (int j = 0; j < nodes; j++) {
            tree[i][j * gap + gap / 2] = 'o';
        }
    }

    for (int i = 0; i < m - 1; i++) {
        int nodes = 1 << i;
        int gap = width / nodes;
        for (int j = 0; j < nodes; j++) {
            int pos = j * gap + gap / 2;
            tree[i + 1][pos - 1] = '/';
            tree[i + 1][pos + 1] = '\\';
        }
    }
}

void remove_node(int m, int i, int j) {
    int width = 1 << (m - 1);
    int nodes = 1 << (i - 1);
    int gap = width / nodes;
    int pos = (j - 1) * gap + gap / 2;

    if (i > 1) {
        int parent_pos = ((j - 1) / 2) * (gap * 2) + gap;
        if (j % 2 == 1) {
            tree[i - 1][parent_pos + 1] = ' ';
        } else {
            tree[i - 1][parent_pos - 1] = ' ';
        }
    }

    for (int k = i; k < m; k++) {
        int child_nodes = 1 << (k - 1);
        int child_gap = width / child_nodes;
        int child_pos = (j - 1) * child_gap + child_gap / 2;
        tree[k][child_pos] = ' ';
        if (k < m - 1) {
            tree[k + 1][child_pos - 1] = ' ';
            tree[k + 1][child_pos + 1] = ' ';
        }
    }
}

void print_tree(int m) {
    for (int i = 0; i < m; i++) {
        printf("%s\n", tree[i]);
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    initialize_tree(m);
    draw_full_tree(m);

    for (int k = 0; k < n; k++) {
        int i, j;
        scanf("%d %d", &i, &j);
        remove_node(m, i, j);
    }

    print_tree(m);

    return 0;
}