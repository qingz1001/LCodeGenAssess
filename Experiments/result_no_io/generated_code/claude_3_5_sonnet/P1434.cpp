#include <stdio.h>
#include <string.h>

#define MAX_R 100
#define MAX_C 100

int R, C;
int height[MAX_R][MAX_C];
int dp[MAX_R][MAX_C];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int dfs(int x, int y) {
    if (dp[x][y] != -1) {
        return dp[x][y];
    }
    
    dp[x][y] = 1;
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (nx >= 0 && nx < R && ny >= 0 && ny < C && height[nx][ny] < height[x][y]) {
            int len = dfs(nx, ny) + 1;
            if (len > dp[x][y]) {
                dp[x][y] = len;
            }
        }
    }
    
    return dp[x][y];
}

int main() {
    scanf("%d %d", &R, &C);
    
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &height[i][j]);
        }
    }
    
    memset(dp, -1, sizeof(dp));
    
    int max_length = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int length = dfs(i, j);
            if (length > max_length) {
                max_length = length;
            }
        }
    }
    
    printf("%d\n", max_length);
    
    return 0;
}