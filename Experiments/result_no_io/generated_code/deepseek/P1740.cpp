#include <stdio.h>
#include <stdlib.h>

#define MAXN 888

char grid[MAXN * 2 + 1][MAXN * 2 + 1];
int edges[MAXN * 2 + 1][MAXN * 2 + 1];

int main() {
    int n;
    scanf("%d", &n);

    // Read the input grid
    for (int i = 0; i < 2 * n; i++) {
        scanf("%s", grid[i]);
    }

    // Initialize the edges array
    for (int i = 0; i < 2 * n + 1; i++) {
        for (int j = 0; j < 2 * n + 1; j++) {
            edges[i][j] = 0;
        }
    }

    // Process the grid to determine edges
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * i + 1; j++) {
            if (j % 2 == 0) {
                if (grid[i][j] == '/') {
                    edges[i][j / 2] = 1;
                }
            } else {
                if (grid[i][j] == '\\') {
                    edges[i][j / 2 + 1] = 1;
                }
            }
        }
    }

    for (int i = n; i < 2 * n; i++) {
        for (int j = 0; j < 2 * (2 * n - i) - 1; j++) {
            if (j % 2 == 0) {
                if (grid[i][j] == '\\') {
                    edges[i][j / 2] = 1;
                }
            } else {
                if (grid[i][j] == '/') {
                    edges[i][j / 2 + 1] = 1;
                }
            }
        }
    }

    // Output the edges array
    printf("%d\n", n);
    for (int i = 0; i < 2 * n + 1; i++) {
        for (int j = 0; j < 2 * n + 1; j++) {
            printf("%d", edges[i][j]);
        }
        printf("\n");
    }

    return 0;
}