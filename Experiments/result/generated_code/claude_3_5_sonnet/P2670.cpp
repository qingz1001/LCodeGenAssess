#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 100

char field[MAX_N][MAX_M];
int n, m;

int count_mines(int x, int y) {
    int count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && field[nx][ny] == '*') {
                count++;
            }
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", field[i]);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] == '?') {
                int mines = count_mines(i, j);
                printf("%d", mines);
            } else {
                printf("*");
            }
        }
        printf("\n");
    }
    
    return 0;
}