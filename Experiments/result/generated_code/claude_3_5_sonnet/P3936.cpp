#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20
#define MAX_M 20
#define MAX_C 50

int n, m, c;
int p[MAX_C + 1];
int grid[MAX_N][MAX_M];

void fill_grid(int color, int count) {
    for (int i = 0; i < n && count > 0; i++) {
        for (int j = 0; j < m && count > 0; j++) {
            if (grid[i][j] == 0) {
                grid[i][j] = color;
                count--;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &c);
    
    for (int i = 1; i <= c; i++) {
        scanf("%d", &p[i]);
    }
    
    memset(grid, 0, sizeof(grid));
    
    for (int i = 1; i <= c; i++) {
        fill_grid(i, p[i]);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}