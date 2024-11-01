#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define INF 1000000
#define DIRS 4

typedef struct {
    int x, y, dir, turns;
} State;

int main(){
    int N;
    scanf("%d", &N);
    char grid[MAX][MAX+1];
    int start_x, start_y, end_x, end_y;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            char c;
            scanf(" %c", &c);
            grid[i][j] = c;
            if(c == 'A'){
                start_x = i;
                start_y = j;
            }
            if(c == 'B'){
                end_x = i;
                end_y = j;
            }
        }
    }
    int dx[4]={-1,1,0,0};
    int dy[4]={0,0,-1,1};
    int turns_min[MAX][MAX][DIRS];
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) for(int d=0;d<DIRS;d++) turns_min[i][j][d]=INF;
    State queue[MAX*MAX*DIRS];
    int front=0, back=0;
    for(int d=0;d<DIRS;d++){
        turns_min[start_x][start_y][d]=0;
        queue[back++] = (State){start_x, start_y, d, 0};
    }
    while(front < back){
        State current = queue[front++];
        if(current.x == end_x && current.y == end_y){
            // Do not break here, need to find the minimal among all directions
            continue;
        }
        for(int d=0;d<DIRS;d++){
            int nx = current.x + dx[d];
            int ny = current.y + dy[d];
            if(nx <0 || nx >=N || ny <0 || ny >=N) continue;
            if(grid[nx][ny]=='x') continue;
            int new_turns = current.turns + (d != current.dir ? 1 : 0);
            if(new_turns < turns_min[nx][ny][d]){
                turns_min[nx][ny][d] = new_turns;
                queue[back++] = (State){nx, ny, d, new_turns};
            }
        }
    }
    int result = INF;
    for(int d=0;d<DIRS;d++) if(turns_min[end_x][end_y][d] < result) result = turns_min[end_x][end_y][d];
    if(result == INF) printf("-1\n");
    else printf("%d\n", result);
}