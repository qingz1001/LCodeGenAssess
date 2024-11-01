#include <stdio.h>
#include <stdlib.h>

#define MAXN 20
#define MAXC 50

int n, m, c;
int p[MAXC];
int grid[MAXN][MAXN];

void init_grid() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            grid[i][j] = -1;
        }
    }
}

void place_color(int color, int count) {
    int placed = 0;
    while (placed < count) {
        int row = rand() % n;
        int col = rand() % m;
        if (grid[row][col] == -1) {
            grid[row][col] = color;
            placed++;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 0; i < c; i++) {
        scanf("%d", &p[i]);
    }

    init_grid();

    for (int i = 0; i < c; i++) {
        place_color(i + 1, p[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}