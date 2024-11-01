#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int main() {
    int n;
    scanf("%d", &n);
    int grid[MAXN][MAXN];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }

    int max_score = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 0) {
                int score = 0;
                for (int x = 0; x < n; ++x) {
                    score += grid[x][j];
                }
                for (int y = 0; y < n; ++y) {
                    score += grid[i][y];
                }
                max_score = (max_score > score) ? max_score : score;
            }
        }
    }

    if (max_score == -1) {
        printf("Bad Game!\n");
    } else {
        printf("%d\n", max_score);
    }

    return 0;
}