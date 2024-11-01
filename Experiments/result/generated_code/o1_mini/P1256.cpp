#include <stdio.h>
#include <string.h>

#define MAX 182
#define MAX_QUEUE 33000

typedef struct {
    int x;
    int y;
} Point;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    char grid[MAX][MAX+1];
    for(int i=0;i<N;i++){
        scanf("%s", grid[i]);
    }
    int dist[MAX][MAX];
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            dist[i][j] = -1;
        }
    }
    Point queue[MAX_QUEUE];
    int front=0, rear=0;
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            if(grid[i][j] == '1'){
                dist[i][j] = 0;
                queue[rear].x = i;
                queue[rear].y = j;
                rear++;
            }
        }
    }
    int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
    while(front < rear){
        Point current = queue[front++];
        for(int d=0; d<4; d++) {
            int ni = current.x + dirs[d][0];
            int nj = current.y + dirs[d][1];
            if(ni >=0 && ni < N && nj >=0 && nj < M && dist[ni][nj]==-1){
                dist[ni][nj] = dist[current.x][current.y] + 1;
                queue[rear].x = ni;
                queue[rear].y = nj;
                rear++;
            }
        }
    }
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            printf("%d", dist[i][j]);
            if(j != M-1) printf(" ");
        }
        printf("\n");
    }
    return 0;
}