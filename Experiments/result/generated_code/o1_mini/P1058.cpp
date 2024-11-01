#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_M 50
#define MAX_N 50
#define MAX_H 100
#define MAX_ROWS 1000
#define MAX_COLS 1000

char canvas[MAX_ROWS][MAX_COLS];
int m, n;
int grid[MAX_M][MAX_N];
int maxH = 0;

int main(){
    scanf("%d %d", &m, &n);
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            scanf("%d", &grid[i][j]);
            if(grid[i][j] > maxH) maxH = grid[i][j];
        }
    }
    memset(canvas, '.', sizeof(canvas));
    // Estimate canvas size
    int rows = (m + n) * 2 + maxH * 4 + 10;
    int cols = (m + n) * 4 + maxH * 4 + 10;
    // Initialize canvas with dots
    for(int i=0;i<rows;i++) {
        for(int j=0;j<cols;j++) {
            canvas[i][j] = '.';
        }
    }
    // Starting position
    int baseRow = (m + n) * 2 + maxH * 2;
    int baseCol = maxH * 2;
    // Directions for cube
    int dr[6][6] = {
        {0,1,2,3,4,5},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    };
    // Iterate through each cell
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            for(int k=0;k<grid[i][j];k++) {
                int r = baseRow - (i + j) * 2 - k * 4;
                int c = baseCol + (j - i) * 4 + k * 4;
                // Draw cube
                // Line 0
                if(r >=0 && c+4 < cols){
                    canvas[r][c] = '+';
                    canvas[r][c+1] = '-';
                    canvas[r][c+2] = '-';
                    canvas[r][c+3] = '-';
                    canvas[r][c+4] = '+';
                }
                // Line 1
                if(r+1 < rows && c-1 >=0 && c+4 < cols){
                    canvas[r+1][c-1] = '/';
                    for(int x=0; x<3; x++) canvas[r+1][c+x] = ' ';
                    canvas[r+1][c+3] = '/';
                    canvas[r+1][c+4] = '|';
                }
                // Line 2
                if(r+2 < rows && c >=0 && c+4 < cols){
                    canvas[r+2][c] = '+';
                    canvas[r+2][c+1] = '-';
                    canvas[r+2][c+2] = '-';
                    canvas[r+2][c+3] = '-';
                    canvas[r+2][c+4] = '+';
                    canvas[r+2][c+6] = '|';
                }
                // Line 3
                if(r+3 < rows && c >=0 && c+4 < cols){
                    canvas[r+3][c] = '|';
                    for(int x=1; x<4; x++) canvas[r+3][c+x] = ' ';
                    canvas[r+3][c+4] = '|';
                    canvas[r+3][c+6] = '+';
                }
                // Line 4
                if(r+4 < rows && c >=0 && c+4 < cols){
                    canvas[r+4][c] = '|';
                    for(int x=1; x<4; x++) canvas[r+4][c+x] = ' ';
                    canvas[r+4][c+4] = '|';
                    canvas[r+4][c+6] = '/';
                }
                // Line 5
                if(r+5 < rows && c >=0 && c+4 < cols){
                    canvas[r+5][c] = '+';
                    canvas[r+5][c+1] = '-';
                    canvas[r+5][c+2] = '-';
                    canvas[r+5][c+3] = '-';
                    canvas[r+5][c+4] = '+';
                }
            }
        }
    }
    // Find actual rows and cols
    int finalRows=0, finalCols=0;
    for(int i=0;i<rows;i++) {
        int has =0;
        for(int j=0;j<cols;j++) if(canvas[i][j] != '.') {has=1; break;}
        if(has) finalRows = i+1;
    }
    for(int j=0;j<cols;j++) {
        int has =0;
        for(int i=0;i<rows;i++) if(canvas[i][j] != '.') {has=1; break;}
        if(has) finalCols = j+1;
    }
    // Print
    for(int i=0;i<finalRows;i++) {
        for(int j=0;j<finalCols;j++) putchar(canvas[i][j]);
        putchar('\n');
    }
}