#include <stdio.h>
#include <stdlib.h>

#define MAX 15

int m, n;
int maze[MAX][MAX];
int visited[MAX][MAX];
int path_x[MAX * MAX];
int path_y[MAX * MAX];
int start_x, start_y, end_x, end_y;

void print_path(int length) {
    for(int i = 0; i < length; i++) {
        printf("(%d,%d)", path_x[i], path_y[i]);
        if(i != length -1){
            printf("->");
        }
    }
    printf("\n");
}

int found = 0;

void dfs(int x, int y, int length){
    if(x == end_x && y == end_y){
        print_path(length);
        found = 1;
        return;
    }
    // Directions: left, up, right, down
    int dx[4] = {0, -1, 0, 1};
    int dy[4] = {-1, 0, 1, 0};
    for(int dir = 0; dir <4; dir++){
        int new_x = x + dx[dir];
        int new_y = y + dy[dir];
        if(new_x >=1 && new_x <=m && new_y >=1 && new_y <=n && maze[new_x][new_y] ==1 && !visited[new_x][new_y]){
            visited[new_x][new_y] =1;
            path_x[length] = new_x;
            path_y[length] = new_y;
            dfs(new_x, new_y, length+1);
            visited[new_x][new_y] =0;
        }
    }
}

int main(){
    scanf("%d %d", &m, &n);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            scanf("%d", &maze[i][j]);
        }
    }
    scanf("%d %d", &start_x, &start_y);
    scanf("%d %d", &end_x, &end_y);
    if(maze[start_x][start_y] ==0 || maze[end_x][end_y] ==0){
        printf("-1\n");
        return 0;
    }
    visited[start_x][start_y] =1;
    path_x[0] = start_x;
    path_y[0] = start_y;
    dfs(start_x, start_y,1);
    if(!found){
        printf("-1\n");
    }
    return 0;
}