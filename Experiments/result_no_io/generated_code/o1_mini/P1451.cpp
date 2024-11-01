#include <stdio.h>
#include <string.h>

#define MAX 100

int n, m;
char grid[MAX][MAX + 1];
int visited[MAX][MAX];

void dfs(int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m)
        return;
    if (grid[i][j] == '0' || visited[i][j])
        return;
    visited[i][j] = 1;
    dfs(i-1, j);
    dfs(i+1, j);
    dfs(i, j-1);
    dfs(i, j+1);
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++){
        scanf("%s", grid[i]);
    }
    memset(visited, 0, sizeof(visited));
    int count = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j] != '0' && !visited[i][j]){
                count++;
                dfs(i, j);
            }
        }
    }
    printf("%d\n", count);
    return 0;
}