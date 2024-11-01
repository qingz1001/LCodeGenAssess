#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 100
#define MAX_DIR 8
#define MAX_QUEUE 90000

typedef struct {
    int x;
    int y;
    int prev_dir;
    int steps;
} State;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int grid[MAX_N+1][MAX_M+1];
    for(int y=1;y<=M;y++) {
        for(int x=1;x<=N;x++) {
            scanf("%d", &grid[x][y]);
        }
    }
    if(N ==1 && M ==1){
        printf("0");
        return 0;
    }
    int dx[8] = {-1,-1,0,1,1,1,0,-1};
    int dy[8] = {0,1,1,1,0,-1,-1,-1};
    int visited[MAX_N+1][MAX_M+1][9];
    memset(visited, 0, sizeof(visited));
    State queue[MAX_QUEUE];
    int front=0, rear=0;
    queue[rear++] = (State){1,1,8,0};
    visited[1][1][8] = 1;
    int found = -1;
    while(front < rear){
        State current = queue[front++];
        int X = grid[current.x][current.y];
        for(int d=0; d<8; d++){
            if(current.prev_dir != d){
                int new_x = current.x + dx[d]*X;
                int new_y = current.y + dy[d]*X;
                if(new_x >=1 && new_x <=N && new_y >=1 && new_y <=M){
                    if(!visited[new_x][new_y][d]){
                        visited[new_x][new_y][d] =1;
                        if(new_x == N && new_y == M){
                            found = current.steps +1;
                            printf("%d", found);
                            return 0;
                        }
                        queue[rear++] = (State){new_x, new_y, d, current.steps +1};
                        if(rear >= MAX_QUEUE){
                            break;
                        }
                    }
                }
            }
        }
    }
    printf("NEVER");
    return 0;
}