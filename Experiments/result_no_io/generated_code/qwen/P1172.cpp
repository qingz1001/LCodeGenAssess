#include <stdio.h>
#include <stdlib.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_N 100

int r, c;
int n;
int cows[MAX_N][2];
int grid[MAX_R][MAX_C];

void mark_path(int x, int y) {
    while (x >= 0 && y < c) {
        grid[x--][y++] = 1;
    }
}

int is_safe() {
    for (int i = 0; i < n; i++) {
        int x = cows[i][0] - 1;
        int y = cows[i][1] - 1;
        if (grid[x][y]) return 0;
        mark_path(x, y);
    }
    return 1;
}

int main() {
    scanf("%d %d", &r, &c);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cows[i][0], &cows[i][1]);
        cows[i][0]--;
        cows[i][1]--;
    }

    if (is_safe()) {
        printf("0\n");
    } else {
        int removed[MAX_N] = {0};
        int count = 0;
        for (int i = 0; i < n; i++) {
            int temp_grid[MAX_R][MAX_C];
            for (int j = 0; j < r; j++) {
                for (int k = 0; k < c; k++) {
                    temp_grid[j][k] = grid[j][k];
                }
            }
            int x = cows[i][0];
            int y = cows[i][1];
            temp_grid[x][y] = 0;
            mark_path(x, y);
            if (is_safe()) {
                removed[count++] = i + 1;
            }
            for (int j = 0; j < r; j++) {
                for (int k = 0; k < c; k++) {
                    grid[j][k] = temp_grid[j][k];
                }
            }
        }
        if (count == 0) {
            printf("-1\n");
        } else {
            for (int i = 0; i < count; i++) {
                printf("%d\n", removed[i]);
            }
        }
    }

    return 0;
}