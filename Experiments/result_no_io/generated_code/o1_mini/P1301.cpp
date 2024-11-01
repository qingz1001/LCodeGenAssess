#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x, y, last_dir;
} State;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int magic[N+1][M+1];
    for(int y=1; y<=M; y++) {
        for(int x=1; x<=N; x++) {
            scanf("%d", &magic[x][y]);
        }
    }

    // Directions: N, NE, E, SE, S, SW, W, NW
    int dx[8] = {0,1,1,1,0,-1,-1,-1};
    int dy[8] = {-1,-1,0,1,1,1,0,-1};

    // Visited[x][y][last_dir]
    int visited[N+1][M+1][8];
    memset(visited, -1, sizeof(visited));

    // Queue for BFS
    State queue[100000];
    int front =0, rear=0;

    // Initialize
    for(int d=0; d<8; d++){
        int step = magic[1][1];
        int nx = 1 + dx[d]*step;
        int ny = 1 + dy[d]*step;
        if(nx >=1 && nx <=N && ny >=1 && ny <=M){
            queue[rear].x = nx;
            queue[rear].y = ny;
            queue[rear].last_dir = d;
            rear++;
            visited[nx][ny][d] =1;
        }
    }
    int steps=1;
    while(front < rear){
        int current_level_size = rear - front;
        for(int i=0;i<current_level_size;i++){
            State current = queue[front++];
            if(current.x == N && current.y == M){
                printf("%d", steps);
                return 0;
            }
            int step_size = magic[current.x][current.y];
            for(int d=0; d<8; d++){
                if(d == current.last_dir) continue;
                int nx = current.x + dx[d]*step_size;
                int ny = current.y + dy[d]*step_size;
                if(nx >=1 && nx <=N && ny >=1 && ny <=M && visited[nx][ny][d]==-1){
                    queue[rear].x = nx;
                    queue[rear].y = ny;
                    queue[rear].last_dir = d;
                    rear++;
                    visited[nx][ny][d] =1;
                }
            }
        }
        steps++;
    }
    printf("NEVER");
    return 0;
}