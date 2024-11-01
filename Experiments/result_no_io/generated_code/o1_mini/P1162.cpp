#include <stdio.h>
#include <string.h>

#define MAX 30

int n;
int matrix[MAX][MAX];
int visited[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void dfs(int x, int y){
    if(x < 0 || x >= n || y < 0 || y >= n) return;
    if(matrix[x][y] != 0 || visited[x][y]) return;
    visited[x][y] = 1;
    for(int i=0;i<4;i++){
        dfs(x + dx[i], y + dy[i]);
    }
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    memset(visited, 0, sizeof(visited));
    // Top and Bottom rows
    for(int j=0; j<n; j++){
        if(matrix[0][j] == 0 && !visited[0][j]){
            dfs(0, j);
        }
        if(matrix[n-1][j] == 0 && !visited[n-1][j]){
            dfs(n-1, j);
        }
    }
    // Left and Right columns
    for(int i=0; i<n; i++){
        if(matrix[i][0] == 0 && !visited[i][0]){
            dfs(i, 0);
        }
        if(matrix[i][n-1] == 0 && !visited[i][n-1]){
            dfs(i, n-1);
        }
    }
    // Fill the closed region
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(matrix[i][j] == 0 && !visited[i][j]){
                matrix[i][j] = 2;
            }
        }
    }
    // Print the matrix
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d%c", matrix[i][j], j == n-1 ? '\n' : ' ');
        }
    }
    return 0;
}