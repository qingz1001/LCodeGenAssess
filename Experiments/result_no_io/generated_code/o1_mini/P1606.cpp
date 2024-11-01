#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_M 30
#define MAX_N 30
#define INF 1000000

typedef struct {
    int r;
    int c;
} Position;

typedef struct {
    Position pos;
} QueueNode;

typedef struct {
    QueueNode nodes[MAX_M * MAX_N * 100];
    int front;
    int back;
} Deque;

void initDeque(Deque *dq) {
    dq->front = 0;
    dq->back = 0;
}

int isEmpty(Deque *dq) {
    return dq->front == dq->back;
}

void pushFront(Deque *dq, Position pos) {
    dq->front--;
    dq->nodes[dq->front].pos = pos;
}

void pushBack(Deque *dq, Position pos) {
    dq->nodes[dq->back].pos = pos;
    dq->back++;
}

Position popFrontNode(Deque *dq) {
    return dq->nodes[dq->front].pos;
}

int main(){
    int M, N;
    scanf("%d %d", &M, &N);
    int grid[MAX_M][MAX_N];
    int start_r, start_c, end_r, end_c;
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            scanf("%d", &grid[i][j]);
            if(grid[i][j] == 3){
                start_r = i;
                start_c = j;
                grid[i][j] = 1;
            }
            if(grid[i][j] == 4){
                end_r = i;
                end_c = j;
                grid[i][j] = 1;
            }
        }
    }

    int dr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

    int cost[MAX_M][MAX_N];
    memset(cost, 0x3f, sizeof(cost));
    uint64_t ways[MAX_M][MAX_N];
    memset(ways, 0, sizeof(ways));

    Deque dq;
    initDeque(&dq);
    Position start = {start_r, start_c};
    pushBack(&dq, start);
    cost[start_r][start_c] = 0;
    ways[start_r][start_c] = 1;

    while(!isEmpty(&dq)){
        Position current = popFrontNode(&dq);
        dq.front++;
        int cur_r = current.r;
        int cur_c = current.c;
        for(int i=0;i<8;i++){
            int nr = cur_r + dr[i];
            int nc = cur_c + dc[i];
            if(nr < 0 || nr >= M || nc < 0 || nc >= N)
                continue;
            if(grid[nr][nc] == 2)
                continue;
            int new_cost = cost[cur_r][cur_c];
            if(grid[nr][nc] == 0){
                new_cost += 1;
            }
            // If stepping on existing pad, no additional cost
            // Otherwise, need to add a pad (water cell)
            if(new_cost < cost[nr][nc]){
                cost[nr][nc] = new_cost;
                ways[nr][nc] = ways[cur_r][cur_c];
                Position next = {nr, nc};
                if(grid[nr][nc] == 1){
                    pushFront(&dq, next);
                }
                else{
                    pushBack(&dq, next);
                }
            }
            else if(new_cost == cost[nr][nc]){
                ways[nr][nc] += ways[cur_r][cur_c];
            }
        }
    }

    if(cost[end_r][end_c] == INF){
        printf("-1\n");
    }
    else{
        printf("%d\n", cost[end_r][end_c]);
        printf("%llu\n", ways[end_r][end_c]);
    }

    return 0;
}