#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1001
#define INF 1000000000
#define DIRS 4

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point data[MAX*MAX];
    int head;
    int tail;
} Deque;

void initDeque(Deque *dq) {
    dq->head = 0;
    dq->tail = 0;
}

int isEmpty(Deque *dq) {
    return dq->head == dq->tail;
}

void pushFront(Deque *dq, int x, int y) {
    dq->head = (dq->head - 1 + MAX*MAX) % (MAX*MAX);
    dq->data[dq->head].x = x;
    dq->data[dq->head].y = y;
}

void pushBack(Deque *dq, int x, int y) {
    dq->data[dq->tail].x = x;
    dq->data[dq->tail].y = y;
    dq->tail = (dq->tail + 1) % (MAX*MAX);
}

Point popFront(Deque *dq) {
    Point p = dq->data[dq->head];
    dq->head = (dq->head + 1) % (MAX*MAX);
    return p;
}

int main(){
    int n, x0, y0;
    scanf("%d %d %d", &n, &x0, &y0);
    int grid[MAX][MAX];
    memset(grid, 0, sizeof(grid));
    for(int i=0;i<n;i++){
        int xi, yi;
        scanf("%d %d", &xi, &yi);
        if(xi >=0 && xi < MAX && yi >=0 && yi < MAX)
            grid[xi][yi] = 1;
    }
    int dist[MAX][MAX];
    for(int i=0;i<MAX;i++) {
        for(int j=0;j<MAX;j++) {
            dist[i][j] = INF;
        }
    }
    if(x0 >= MAX) x0 = MAX-1;
    if(y0 >= MAX) y0 = MAX-1;
    dist[x0][y0] = 0;
    Deque dq;
    initDeque(&dq);
    pushBack(&dq, x0, y0);
    int dx[DIRS] = {1, -1, 0, 0};
    int dy[DIRS] = {0, 0, 1, -1};
    while(!isEmpty(&dq)){
        Point current = popFront(&dq);
        int x = current.x;
        int y = current.y;
        if(x == 0 && y == 0){
            break;
        }
        for(int d=0;d<DIRS;d++){
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(nx >=0 && nx < MAX && ny >=0 && ny < MAX){
                int cost = dist[x][y] + grid[nx][ny];
                if(cost < dist[nx][ny]){
                    dist[nx][ny] = cost;
                    if(grid[nx][ny]==0){
                        pushFront(&dq, nx, ny);
                    }
                    else{
                        pushBack(&dq, nx, ny);
                    }
                }
            }
        }
    }
    printf("%d\n", dist[0][0]);
    return 0;
}