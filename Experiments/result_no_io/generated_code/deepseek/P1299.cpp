#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_COORD 2001 // 2000 + 1 for 0-based indexing

typedef struct {
    int x1, y1, x2, y2;
} Cut;

int grid[MAX_COORD][MAX_COORD];

void dfs(int x, int y) {
    if (x < 0 || x >= MAX_COORD || y < 0 || y >= MAX_COORD || grid[x][y] == 1) {
        return;
    }
    grid[x][y] = 1;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int main() {
    int N;
    scanf("%d", &N);

    Cut cuts[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &cuts[i].x1, &cuts[i].y1, &cuts[i].x2, &cuts[i].y2);
        cuts[i].x1 += 1000;
        cuts[i].y1 += 1000;
        cuts[i].x2 += 1000;
        cuts[i].y2 += 1000;
    }

    for (int i = 0; i < N; i++) {
        if (cuts[i].x1 == cuts[i].x2) {
            int x = cuts[i].x1;
            for (int y = cuts[i].y1; y < cuts[i].y2; y++) {
                grid[x][y] = 1;
            }
        } else {
            int y = cuts[i].y1;
            for (int x = cuts[i].x1; x < cuts[i].x2; x++) {
                grid[x][y] = 1;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < MAX_COORD; i++) {
        for (int j = 0; j < MAX_COORD; j++) {
            if (grid[i][j] == 0) {
                count++;
                dfs(i, j);
            }
        }
    }

    printf("%d\n", count);

    return 0;
}