#include <stdio.h>
#include <math.h>

#define MAXN 105

int main() {
    int n, m, r;
    scanf("%d %d %d", &n, &m, &r);
    int grid[MAXN][MAXN] = {0};
    
    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        for (int j = -r; j <= r; ++j) {
            for (int k = -r; k <= r; ++k) {
                if (j * j + k * k <= r * r && x + j >= 1 && x + j <= n && y + k >= 1 && y + k <= n) {
                    grid[x + j][y + k] = 1;
                }
            }
        }
    }
    
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (grid[i][j]) {
                count++;
            }
        }
    }
    
    printf("%d\n", count);
    return 0;
}