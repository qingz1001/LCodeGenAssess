#include <stdio.h>
#include <string.h>

#define MAX_N 888
#define MAX_SIZE (2 * MAX_N)

char grid[MAX_SIZE][MAX_SIZE];
int n;

int count_parallelograms() {
    int count = 0;
    for (int i = 0; i < 2 * n - 1; i++) {
        for (int j = 0; j < 2 * n - 1; j++) {
            for (int h = 1; h < n; h++) {
                for (int w = 1; w < n; w++) {
                    if (i + h < 2 * n - 1 && j + w < 2 * n - 1) {
                        if (grid[i][j] != ' ' && grid[i][j+w] != ' ' &&
                            grid[i+h][j] != ' ' && grid[i+h][j+w] != ' ' &&
                            grid[i][j] == grid[i+h][j+w] &&
                            grid[i][j+w] == grid[i+h][j]) {
                            int is_empty = 1;
                            for (int y = i + 1; y < i + h && is_empty; y++) {
                                for (int x = j + 1; x < j + w && is_empty; x++) {
                                    if (grid[y][x] != ' ') {
                                        is_empty = 0;
                                    }
                                }
                            }
                            if (is_empty) {
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    scanf("%d", &n);
    memset(grid, ' ', sizeof(grid));
    
    for (int i = 0; i < n; i++) {
        for (int j = n - i - 1; j < n + i + 1; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i; j < 2 * n - i - 1; j++) {
            scanf(" %c", &grid[n + i][j]);
        }
    }
    
    printf("%d\n", count_parallelograms());
    return 0;
}