#include <stdio.h>
#include <stdbool.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_N 100

typedef struct {
    int row;
    int col;
} Cow;

Cow cows[MAX_N];
bool grid[MAX_R][MAX_C];
int r, c, n;

bool isSafe(int exclude) {
    bool tempGrid[MAX_R][MAX_C];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            tempGrid[i][j] = grid[i][j];
        }
    }

    if (exclude != -1) {
        tempGrid[cows[exclude].row][cows[exclude].col] = false;
    }

    for (int i = 0; i < n; i++) {
        if (i == exclude) continue;
        int row = cows[i].row;
        int col = cows[i].col;

        // Check north
        for (int k = row - 1; k >= 0; k--) {
            if (tempGrid[k][col]) return false;
        }

        // Check east
        for (int k = col + 1; k < c; k++) {
            if (tempGrid[row][k]) return false;
        }
    }

    return true;
}

int main() {
    scanf("%d %d", &r, &c);
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cows[i].row, &cows[i].col);
        cows[i].row--;
        cows[i].col--;
        grid[cows[i].row][cows[i].col] = true;
    }

    if (isSafe(-1)) {
        printf("0\n");
        return 0;
    }

    bool found = false;
    for (int i = 0; i < n; i++) {
        if (isSafe(i)) {
            printf("%d\n", i + 1);
            found = true;
        }
    }

    if (!found) {
        printf("-1\n");
    }

    return 0;
}