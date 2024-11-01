#include <stdio.h>
#include <stdlib.h>

#define MAX 196

int m, n;
int grid[15][15];
int visited[15][15];
int pathX[MAX], pathY[MAX];
int pathLen = 0;
int found = 0;

int startX, startY, endX, endY;

void printPath(int len) {
    for(int i=0;i<len;i++) {
        printf("(%d,%d)", pathX[i], pathY[i]);
        if(i != len-1) printf("->");
    }
    printf("\n");
}

void dfs(int x, int y) {
    if(x == endX && y == endY){
        printPath(pathLen);
        found = 1;
        return;
    }
    // Directions: left, up, right, down
    int dirs[4][2] = { {0,-1}, {-1,0}, {0,1}, {1,0} };
    for(int i=0;i<4;i++) {
        int newX = x + dirs[i][0];
        int newY = y + dirs[i][1];
        if(newX >=1 && newX <=m && newY >=1 && newY <=n && grid[newX][newY]==1 && !visited[newX][newY]){
            visited[newX][newY] = 1;
            pathX[pathLen] = newX;
            pathY[pathLen] = newY;
            pathLen++;
            dfs(newX, newY);
            pathLen--;
            visited[newX][newY] = 0;
        }
    }
}

int main(){
    scanf("%d %d", &m, &n);
    for(int i=1;i<=m;i++) {
        for(int j=1;j<=n;j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    scanf("%d %d", &startX, &startY);
    scanf("%d %d", &endX, &endY);
    if(grid[startX][startY] !=1 || grid[endX][endY]!=1){
        printf("-1\n");
        return 0;
    }
    visited[startX][startY] =1;
    pathX[pathLen] = startX;
    pathY[pathLen] = startY;
    pathLen++;
    dfs(startX, startY);
    if(!found) printf("-1\n");
    return 0;
}