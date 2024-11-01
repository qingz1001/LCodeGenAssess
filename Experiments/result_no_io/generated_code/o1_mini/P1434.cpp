#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int R, C;
int grid[MAX][MAX];
int memo[MAX][MAX];
int visited[MAX][MAX];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int max(int a, int b){
    return a > b ? a : b;
}

int dfs(int r, int c){
    if(memo[r][c] != -1){
        return memo[r][c];
    }
    memo[r][c] = 1;
    for(int i = 0;i < 4;i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(nr >=0 && nr < R && nc >=0 && nc < C && grid[nr][nc] < grid[r][c]){
            memo[r][c] = max(memo[r][c], 1 + dfs(nr, nc));
        }
    }
    return memo[r][c];
}

int main(){
    scanf("%d %d", &R, &C);
    for(int i =0;i < R;i++){
        for(int j =0;j < C;j++){
            scanf("%d", &grid[i][j]);
            memo[i][j] = -1;
        }
    }
    int result = 0;
    for(int i =0;i < R;i++){
        for(int j =0;j < C;j++){
            int path = dfs(i, j);
            if(path > result){
                result = path;
            }
        }
    }
    printf("%d", result);
    return 0;
}