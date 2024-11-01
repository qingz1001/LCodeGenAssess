#include <stdio.h>

#define MAX_M 50
#define MAX_N 50
#define MAX_HEIGHT 100

void printBlock(int height) {
    if (height == 0) return;
    printf("+");
    for (int i = 0; i < height - 1; i++) printf("-");
    printf("+");
    for (int i = 0; i < height - 1; i++) printf("/");
    printf("|");
    for (int i = 0; i < height - 1; i++) printf(" ");
    printf("\n");
}

void printRow(int row[], int n) {
    for (int j = 0; j < n; j++) {
        printBlock(row[j]);
    }
    printf("\n");
}

void printGrid(int grid[MAX_M][MAX_N], int m, int n) {
    for (int i = 0; i < m; i++) {
        printRow(grid[i], n);
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int grid[MAX_M][MAX_N];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    printGrid(grid, m, n);

    return 0;
}