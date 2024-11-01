#include <stdio.h>
#include <string.h>

#define MAX_HEIGHT 1024
#define MAX_WIDTH 2048

char grid[MAX_HEIGHT][MAX_WIDTH + 1];

void draw(int x, int y, int size) {
    if (size == 2) {
        grid[x][y] = '/';
        grid[x][y + 1] = '\\';
        grid[x + 1][y - 1] = '/';
        grid[x + 1][y] = '_';
        grid[x + 1][y + 1] = '_';
        grid[x + 1][y + 2] = '\\';
    } else {
        int half = size / 2;
        draw(x, y, half);
        draw(x + half, y - half, half);
        draw(x + half, y + half, half);
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int height = 1 << n;
    int width = 2 * height;
    
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            grid[i][j] = ' ';
        }
        grid[i][width] = '\0';
    }
    
    draw(0, height -1, height);
    
    for(int i = 0; i < height; i++) {
        int last = width -1;
        while(last >=0 && grid[i][last] == ' ') last--;
        for(int j = 0; j <= last; j++) {
            putchar(grid[i][j]);
        }
        putchar('\n');
    }
    
    return 0;
}