#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define WORD "yizhong"

char matrix[MAX_N][MAX_N];
char result[MAX_N][MAX_N];
int n;

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

void find_word(int x, int y, int direction) {
    int len = strlen(WORD);
    int i, nx, ny;
    
    for (i = 0; i < len; i++) {
        nx = x + i * dx[direction];
        ny = y + i * dy[direction];
        
        if (!is_valid(nx, ny) || matrix[nx][ny] != WORD[i]) {
            return;
        }
    }
    
    for (i = 0; i < len; i++) {
        nx = x + i * dx[direction];
        ny = y + i * dy[direction];
        result[nx][ny] = WORD[i];
    }
}

int main() {
    int i, j, k;
    
    scanf("%d", &n);
    
    for (i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }
    
    memset(result, '*', sizeof(result));
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (matrix[i][j] == 'y') {
                for (k = 0; k < 8; k++) {
                    find_word(i, j, k);
                }
            }
        }
    }
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%c", result[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}