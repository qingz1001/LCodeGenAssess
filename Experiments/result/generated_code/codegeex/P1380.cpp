#include <stdio.h>

int n, m, max_tiles = 0;

void dfs(int x, int y, int tiles) {
    if (x >= n || y >= m) {
        if (tiles > max_tiles) max_tiles = tiles;
        return;
    }
    
    // Check if we can place a T tile at (x, y)
    if (x + 2 < n && y + 1 < m && x - 1 >= 0 && y - 1 >= 0) {
        // Place the T tile and move to the next position
        dfs(x + 1, y - 1, tiles + 1);
    }
    
    // Continue searching without placing a T tile
    dfs(x, y + 1, tiles);
}

int main() {
    scanf("%d%d", &n, &m);
    
    // Start the DFS from the top-left corner of the board
    dfs(0, 0, 0);
    
    printf("%d\n", max_tiles);
    return 0;
}