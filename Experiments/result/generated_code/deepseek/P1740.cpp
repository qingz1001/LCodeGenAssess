#include <stdio.h>
#include <stdlib.h>

#define MAXN 888

char grid[MAXN * 2 + 1][MAXN * 2 + 1];
int edges[MAXN * 2 + 1][MAXN * 2 + 1];

void read_input(int n) {
    for (int i = 0; i < 2 * n; i++) {
        scanf("%s", grid[i]);
    }
}

void process_grid(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * i + 1; j++) {
            if (j % 2 == 0) {
                edges[i][j] = (grid[i][j] == '\\') ? 1 : 0;
            } else {
                edges[i][j] = (grid[i][j] == '/') ? 1 : 0;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * (n - i) - 1; j++) {
            if (j % 2 == 0) {
                edges[n + i][j] = (grid[n + i][j] == '/') ? 1 : 0;
            } else {
                edges[n + i][j] = (grid[n + i][j] == '\\') ? 1 : 0;
            }
        }
    }
}

void print_edges(int n) {
    for (int i = 0; i < 2 * n + 1; i++) {
        for (int j = 0; j < 2 * n + 1; j++) {
            if (i < n) {
                if (j < 2 * i + 1) {
                    printf("%d", edges[i][j]);
                } else {
                    printf(" ");
                }
            } else {
                if (j < 2 * (2 * n - i) + 1) {
                    printf("%d", edges[i][j]);
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);
    read_input(n);
    process_grid(n);
    print_edges(n);
    return 0;
}