#include <stdio.h>
#include <stdlib.h>

#define MAX 182

typedef struct {
    int x;
    int y;
} Point;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int grid[MAX][MAX];
    int dist[MAX][MAX];
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            scanf("%d", &grid[i][j]);
            if(grid[i][j]==1){
                dist[i][j]=0;
            }
            else{
                dist[i][j]=-1;
            }
        }
    }
    Point queue[MAX*MAX];
    int front=0, rear=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(grid[i][j]==1){
                queue[rear].x = i;
                queue[rear].y = j;
                rear++;
            }
        }
    }
    int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    while(front < rear){
        int x = queue[front].x;
        int y = queue[front].y;
        front++;
        for(int d=0;d<4;d++){
            int nx = x + dirs[d][0];
            int ny = y + dirs[d][1];
            if(nx >=0 && nx < N && ny >=0 && ny < M && dist[nx][ny]==-1){
                dist[nx][ny] = dist[x][y] + 1;
                queue[rear].x = nx;
                queue[rear].y = ny;
                rear++;
            }
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(j>0) printf(" ");
            printf("%d", dist[i][j]);
        }
        printf("\n");
    }
    return 0;
}