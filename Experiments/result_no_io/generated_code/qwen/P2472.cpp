#include <stdio.h>
#include <stdlib.h>

#define MAXR 20
#define MAXC 20

int r, c, d;
int grid[MAXR][MAXC];
char lizard[MAXR][MAXC];

int min(int a, int b) {
    return (a < b) ? a : b;
}

void dfs(int x, int y, int height, int *escaped) {
    if (x < 0 || x >= r || y < 0 || y >= c || grid[x][y] == 0 || abs(grid[x][y] - height) > d) {
        return;
    }
    if (grid[x][y] == 1) {
        (*escaped)++;
        return;
    }
    grid[x][y]--;
    dfs(x + 1, y, height, escaped);
    dfs(x - 1, y, height, escaped);
    dfs(x, y + 1, height, escaped);
    dfs(x, y - 1, height, escaped);
    grid[x][y]++;
}

int main() {
    scanf("%d %d %d", &r, &c, &d);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf(" %c", &lizard[i][j]);
        }
    }

    int total_lizards = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (lizard[i][j] == 'L') {
                total_lizards++;
                int escaped = 0;
                dfs(i, j, grid[i][j], &escaped);
                printf("%d ", escaped);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }

    printf("%d\n", total_lizards);

    return 0;
}