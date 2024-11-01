#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1024

void draw(char grid[MAX_SIZE][MAX_SIZE], int n, int x, int y) {
    if (n == 1) {
        grid[y][x] = '/';
        grid[y][x+1] = '\\';
        grid[y+1][x-1] = '/';
        grid[y+1][x] = '_';
        grid[y+1][x+1] = '_';
        grid[y+1][x+2] = '\\';
        return;
    }
    
    int size = 1 << (n-1);
    draw(grid, n-1, x, y);
    draw(grid, n-1, x-size, y+size);
    draw(grid, n-1, x+size, y+size);
}

int main() {
    int n;
    scanf("%d", &n);
    
    char grid[MAX_SIZE][MAX_SIZE];
    memset(grid, ' ', sizeof(grid));
    
    int size = 1 << n;
    draw(grid, n, size-1, 0);
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size*2; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}