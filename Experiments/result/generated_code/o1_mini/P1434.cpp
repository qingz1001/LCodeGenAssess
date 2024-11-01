#include <stdio.h>
#define MAX 100

int R, C;
int grid[MAX][MAX];
int dp_cache[MAX][MAX];
int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

int max(int a, int b) {
    return a > b ? a : b;
}

int memo(int r, int c) {
    if(dp_cache[r][c] != 0)
        return dp_cache[r][c];
    dp_cache[r][c] = 1;
    for(int d = 0; d < 4; d++) {
        int nr = r + dirs[d][0];
        int nc = c + dirs[d][1];
        if(nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] < grid[r][c]) {
            dp_cache[r][c] = max(dp_cache[r][c], 1 + memo(nr, nc));
        }
    }
    return dp_cache[r][c];
}

int main(){
    scanf("%d %d", &R, &C);
    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++)
            scanf("%d", &grid[i][j]);
    int result = 0;
    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++)
            result = max(result, memo(i, j));
    printf("%d", result);
    return 0;
}