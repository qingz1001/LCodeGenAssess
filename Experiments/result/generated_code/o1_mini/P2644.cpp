#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 30
#define MAX_N 30
#define MAX_P 1000
#define INF 1000000000

typedef long long ll;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int S;
    ll WS;
    int G;
    ll WG;
} CellInfo;

// Directions for knight moves
int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

int main(){
    int P, M, N;
    scanf("%d %d %d", &P, &M, &N);
    int grid[MAX_M][MAX_N];
    Position start, end;
    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            scanf("%d", &grid[i][j]);
            if(grid[i][j] == 3){
                start.x = i;
                start.y = j;
                grid[i][j] = 1;
            }
            if(grid[i][j] == 4){
                end.x = i;
                end.y = j;
                grid[i][j] = 1;
            }
        }
    }
    CellInfo info[MAX_M][MAX_N];
    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            info[i][j].S = INF;
            info[i][j].WS = 0;
            info[i][j].G = -1;
            info[i][j].WG = 0;
        }
    }
    // Initialize start
    info[start.x][start.y].S = 0;
    info[start.x][start.y].WS = 1;
    info[start.x][start.y].G = 0;
    info[start.x][start.y].WG = 1;
    
    // Priority queue implemented as a simple queue since grid is small
    typedef struct QueueNode {
        int x, y;
    } QueueNode;
    QueueNode queue[MAX_M * MAX_N];
    int front = 0, back = 0;
    queue[back++] = (QueueNode){start.x, start.y};
    
    while(front < back){
        QueueNode current = queue[front++];
        int cx = current.x;
        int cy = current.y;
        for(int d=0; d<8; d++){
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if(nx <0 || nx >= M || ny <0 || ny >= N) continue;
            if(grid[nx][ny] == 2) continue;
            // Calculate cost to make nx,ny a lotus
            int cost = 0;
            int g = 0;
            if(grid[nx][ny] == 0){
                cost = 1;
            }
            else if(grid[nx][ny] ==1){
                cost = 0;
            }
            else if(grid[nx][ny] ==5){
                cost = 2;
                g =1;
            }
            else{
                continue;
            }
            int newS = info[cx][cy].S + cost;
            if(newS > P) continue;
            if(newS < info[nx][ny].S){
                info[nx][ny].S = newS;
                info[nx][ny].WS = info[cx][cy].WS;
                info[nx][ny].G = info[cx][cy].G + g;
                info[nx][ny].WG = info[cx][cy].WG;
                queue[back++] = (QueueNode){nx, ny};
            }
            else if(newS == info[nx][ny].S){
                info[nx][ny].WS += info[cx][cy].WS;
                if(info[cx][cy].G + g > info[nx][ny].G){
                    info[nx][ny].G = info[cx][cy].G + g;
                    info[nx][ny].WG = info[cx][cy].WG;
                }
                else if(info[cx][cy].G + g == info[nx][ny].G){
                    info[nx][ny].WG += info[cx][cy].WG;
                }
            }
        }
    }
    if(info[end.x][end.y].S == INF || info[end.x][end.y].S > P){
        printf("-1\n");
        return 0;
    }
    printf("%d %lld\n", info[end.x][end.y].S, info[end.x][end.y].WS);
    if(info[end.x][end.y].G == -1){
        printf("-1\n");
    }
    else{
        printf("%d %lld\n", info[end.x][end.y].G, info[end.x][end.y].WG);
    }
    return 0;
}