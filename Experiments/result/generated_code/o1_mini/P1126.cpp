#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50
#define MAXQ 100000

typedef struct {
    int x;
    int y;
    int dir;
} State;

int grid[MAXN][MAXN];
int N, M;
int visited_MAXN_MAXN_MAXDIR;
int visited[51][51][4];
int front=0, rear=0;
State queue_states[MAXQ];
int queue_dirs[MAXQ];
int queue_steps[MAXQ];

int is_safe(int x, int y){
    for(int dx=-1; dx<=1; dx++) {
        for(int dy=-1; dy<=1; dy++) {
            int nx = x + dx;
            int ny = y + dy;
            if(nx <0 || nx>=N || ny <0 || ny>=M)
                return 0;
            if(grid[nx][ny]==1)
                return 0;
        }
    }
    return 1;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    int sr, sc, tr, tc;
    char sd;
    scanf("%d %d %d %d %c", &sr, &sc, &tr, &tc, &sd);
    sr--; sc--; tr--; tc--;
    int start_dir;
    if(sd == 'E') start_dir=0;
    else if(sd == 'S') start_dir=1;
    else if(sd == 'W') start_dir=2;
    else start_dir=3;
    if(!is_safe(sr, sc) || !is_safe(tr, tc)){
        printf("-1");
        return 0;
    }
    queue_states[rear].x = sr;
    queue_states[rear].y = sc;
    queue_states[rear].dir = start_dir;
    rear++;
    visited[sr][sc][start_dir]=1;
    int time=0;
    int dirs[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    while(front < rear){
        int qsize = rear - front;
        for(int i=0;i<qsize;i++){
            State current = queue_states[front];
            if(current.x == tr && current.y == tc){
                printf("%d", time);
                return 0;
            }
            // Turn Left
            int new_dir = (current.dir +3)%4;
            if(!visited[current.x][current.y][new_dir]){
                visited[current.x][current.y][new_dir]=1;
                queue_states[rear].x = current.x;
                queue_states[rear].y = current.y;
                queue_states[rear].dir = new_dir;
                rear++;
            }
            // Turn Right
            new_dir = (current.dir +1)%4;
            if(!visited[current.x][current.y][new_dir]){
                visited[current.x][current.y][new_dir]=1;
                queue_states[rear].x = current.x;
                queue_states[rear].y = current.y;
                queue_states[rear].dir = new_dir;
                rear++;
            }
            // Move Creep, Walk, Run
            for(int steps=1; steps<=3; steps++){
                int nx = current.x;
                int ny = current.y;
                int ok=1;
                for(int step=0; step<steps; step++){
                    nx += dirs[current.dir][0];
                    ny += dirs[current.dir][1];
                    if(!is_safe(nx, ny)){
                        ok=0;
                        break;
                    }
                }
                if(ok && !visited[nx][ny][current.dir]){
                    visited[nx][ny][current.dir]=1;
                    queue_states[rear].x = nx;
                    queue_states[rear].y = ny;
                    queue_states[rear].dir = current.dir;
                    rear++;
                }
            }
            front++;
        }
        time++;
    }
    printf("-1");
    return 0;
}