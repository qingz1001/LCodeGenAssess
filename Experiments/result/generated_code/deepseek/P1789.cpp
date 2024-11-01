#include <stdio.h>
#include <stdbool.h>

#define MAXN 100

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    bool grid[MAXN][MAXN] = {false}; // false means dark, true means light
    
    // Process torches
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--; // Convert to 0-based index
        
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    if (dx * dx + dy * dy <= 4) { // Check if within light range
                        grid[nx][ny] = true;
                    }
                }
            }
        }
    }
    
    // Process glowstones
    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--; // Convert to 0-based index
        
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    grid[nx][ny] = true;
                }
            }
        }
    }
    
    // Count dark spots
    int dark_spots = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!grid[i][j]) {
                dark_spots++;
            }
        }
    }
    
    printf("%d\n", dark_spots);
    
    return 0;
}