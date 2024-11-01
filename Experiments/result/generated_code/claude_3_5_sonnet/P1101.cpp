#include <stdio.h>
#include <string.h>

#define MAX_N 100

char matrix[MAX_N][MAX_N];
char result[MAX_N][MAX_N];
int n;

const char target[] = "yizhong";
const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int dfs(int x, int y, int direction, int index) {
    if (index == 7) return 1;
    
    int nx = x + dx[direction];
    int ny = y + dy[direction];
    
    if (nx < 0 || nx >= n || ny < 0 || ny >= n) return 0;
    if (matrix[nx][ny] != target[index]) return 0;
    
    return dfs(nx, ny, direction, index + 1);
}

void mark_word(int x, int y, int direction) {
    for (int i = 0; i < 7; i++) {
        result[x][y] = matrix[x][y];
        x += dx[direction];
        y += dy[direction];
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
        memset(result[i], '*', n);
        result[i][n] = '\0';
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 'y') {
                for (int d = 0; d < 8; d++) {
                    if (dfs(i, j, d, 1)) {
                        mark_word(i, j, d);
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        printf("%s\n", result[i]);
    }
    
    return 0;
}