#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int x, y, dir, steps;
} State;

int N, M;
int grid[52][52];
int visited[52][52][4];
int dx[4] = {0, 1, 0, -1}; // E, S, W, N
int dy[4] = {1, 0, -1, 0};

int is_safe(int x, int y){
    for(int i = x-1;i<=x+1;i++) {
        for(int j = y-1;j<=y+1;j++) {
            if(i<1 || i>N || j<1 || j>M || grid[i][j]==1)
                return 0;
        }
    }
    return 1;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=M;j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    int sx, sy, tx, ty;
    char dir_char;
    scanf("%d %d %c %d %d", &sx, &sy, &dir_char, &tx, &ty);
    int dir;
    switch(dir_char){
        case 'E': dir=0; break;
        case 'S': dir=1; break;
        case 'W': dir=2; break;
        case 'N': dir=3; break;
    }
    memset(visited, 0, sizeof(visited));
    State queue[100000];
    int front=0, rear=0;
    queue[rear++] = (State){sx, sy, dir, 0};
    visited[sx][sy][dir] = 1;
    while(front < rear){
        State current = queue[front++];
        if(current.x == tx && current.y == ty){
            printf("%d", current.steps);
            return 0;
        }
        // Turn Left
        int ndir = (current.dir + 3) % 4;
        if(!visited[current.x][current.y][ndir]){
            visited[current.x][current.y][ndir]=1;
            queue[rear++] = (State){current.x, current.y, ndir, current.steps+1};
        }
        // Turn Right
        ndir = (current.dir +1) %4;
        if(!visited[current.x][current.y][ndir]){
            visited[current.x][current.y][ndir]=1;
            queue[rear++] = (State){current.x, current.y, ndir, current.steps+1};
        }
        // Move forward 1,2,3
        for(int k=1;k<=3;k++){
            int nx = current.x + dx[current.dir]*k;
            int ny = current.y + dy[current.dir]*k;
            int valid=1;
            for(int step=1; step<=k; step++){
                int txp = current.x + dx[current.dir]*step;
                int typ = current.y + dy[current.dir]*step;
                if(!is_safe(txp, typ)){
                    valid=0;
                    break;
                }
            }
            if(valid && !visited[nx][ny][current.dir]){
                visited[nx][ny][current.dir]=1;
                queue[rear++] = (State){nx, ny, current.dir, current.steps+1};
            }
        }
    }
    printf("-1");
}