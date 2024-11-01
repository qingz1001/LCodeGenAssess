#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 20
#define MAXM 20
#define MAXQ 400

typedef struct {
    int x, y;
} Point;

int N, M;
char grid[MAXN][MAXM + 1];
int dist_map[MAXN][MAXM];
int doors[MAXN * MAXM][2];
int door_count = 0;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int queue_x[MAXQ];
int queue_y[MAXQ];
int front, rear;

int main(){
    scanf("%d %d", &N, &M);
    for(int i=0;i<N;i++) {
        scanf("%s", grid[i]);
    }
    memset(dist_map, -1, sizeof(dist_map));
    // Find doors
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            if(grid[i][j]=='D'){
                doors[door_count][0] = i;
                doors[door_count][1] = j;
                door_count++;
            }
        }
    }
    // BFS from all doors
    front = rear =0;
    for(int i=0;i<door_count;i++){
        int x = doors[i][0];
        int y = doors[i][1];
        queue_x[rear] = x;
        queue_y[rear] = y;
        rear++;
        dist_map[x][y] = 0;
    }
    while(front < rear){
        int x = queue_x[front];
        int y = queue_y[front];
        front++;
        for(int d=0;d<4;d++){
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(nx >=0 && nx <N && ny >=0 && ny <M && grid[nx][ny] !='X' && dist_map[nx][ny]==-1){
                dist_map[nx][ny] = dist_map[x][y] +1;
                queue_x[rear] = nx;
                queue_y[rear] = ny;
                rear++;
            }
        }
    }
    // Collect distances
    int distances[MAXN*MAXM];
    int total =0;
    int impossible =0;
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            if(grid[i][j]=='.'){
                if(dist_map[i][j]==-1){
                    impossible =1;
                }
                distances[total++] = dist_map[i][j];
            }
        }
    }
    if(impossible){
        printf("impossible");
        return 0;
    }
    // Sort distances
    for(int i=0;i<total-1;i++) {
        for(int j=i+1;j<total;j++) {
            if(distances[i] > distances[j]){
                int tmp = distances[i];
                distances[i] = distances[j];
                distances[j] = tmp;
            }
        }
    }
    // Calculate evacuation time
    int max_time =0;
    for(int i=0;i<total;i++) {
        int t = distances[i] + (i / door_count) +1;
        if(t > max_time) max_time = t;
    }
    printf("%d", max_time);
    return 0;
}