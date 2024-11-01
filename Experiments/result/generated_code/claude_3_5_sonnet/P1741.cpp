#include <stdio.h>
#include <string.h>

#define MAXN 888
#define MAXM 1777

char grid[MAXM][MAXM];
int n, count = 0;

void count_parallelograms(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    if (x1 < 0 || x1 >= 2*n-1 || y1 < 0 || y1 >= 2*n-1 ||
        x2 < 0 || x2 >= 2*n-1 || y2 < 0 || y2 >= 2*n-1 ||
        x3 < 0 || x3 >= 2*n-1 || y3 < 0 || y3 >= 2*n-1 ||
        x4 < 0 || x4 >= 2*n-1 || y4 < 0 || y4 >= 2*n-1)
        return;

    if (grid[x1][y1] == ' ' || grid[x2][y2] == ' ' || grid[x3][y3] == ' ' || grid[x4][y4] == ' ')
        return;

    int empty = 1;
    for (int i = x1+1; i < x3 && empty; i++)
        for (int j = y1+1; j < y2 && empty; j++)
            if (grid[i][j] != ' ')
                empty = 0;

    if (empty) count++;
}

int main() {
    scanf("%d", &n);
    getchar();

    memset(grid, ' ', sizeof(grid));

    for (int i = 0; i < n; i++) {
        for (int j = n-i-1; j < n+i+1; j++) {
            grid[i][j] = getchar();
        }
        getchar();
    }

    for (int i = n; i < 2*n; i++) {
        for (int j = i-n+1; j < 3*n-i-1; j++) {
            grid[i][j] = getchar();
        }
        getchar();
    }

    for (int i = 0; i < 2*n-1; i++) {
        for (int j = 0; j < 2*n-1; j++) {
            for (int k = 1; i+k < 2*n-1 && j+k < 2*n-1; k++) {
                for (int l = 1; i+l < 2*n-1 && j-l >= 0; l++) {
                    count_parallelograms(i, j, i, j+k, i+l, j-l, i+l, j+k-l);
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}