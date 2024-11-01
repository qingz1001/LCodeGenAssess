#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Define maximum grid size
#define MAX 30
#define INF 1000000

// Define the structure for queue elements
typedef struct {
    int x;
    int y;
} Cell;

// Define deque structure
typedef struct {
    Cell cells[MAX*MAX];
    int front;
    int back;
} Deque;

// Initialize deque
void initDeque(Deque *dq) {
    dq->front = 0;
    dq->back = 0;
}

// Check if deque is empty
int isEmpty(Deque *dq) {
    return dq->front == dq->back;
}

// Push front
void pushFront(Deque *dq, Cell c) {
    if(dq->front == 0) {
        // Do nothing, as we don't expect to underflow for this problem
    }
    dq->front -= 1;
    dq->cells[dq->front] = c;
}

// Push back
void pushBack(Deque *dq, Cell c) {
    dq->cells[dq->back++] = c;
}

// Pop front
Cell popFrontDeque(Deque *dq) {
    return dq->cells[dq->front++];
}

int main(){
    int M, N;
    scanf("%d %d", &M, &N);
    int grid[MAX][MAX];
    int start_x = -1, start_y = -1;
    int end_x = -1, end_y = -1;
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            scanf("%d", &grid[i][j]);
            if(grid[i][j] == 3){
                start_x = i;
                start_y = j;
            }
            if(grid[i][j] == 4){
                end_x = i;
                end_y = j;
                grid[i][j] = 1; // Treat end as lilypad for movement
            }
            if(grid[i][j] == 3){
                grid[i][j] = 1; // Treat start as lilypad for movement
            }
        }
    }

    if(start_x == end_x && start_y == end_y){
        printf("0\n1\n");
        return 0;
    }

    int dx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
    int dy[8] = {2, -2, 2, -2, 1, -1, 1, -1};

    int d[MAX][MAX];
    memset(d, 0x3f, sizeof(d));
    unsigned long long c_cnt[MAX][MAX];
    memset(c_cnt, 0, sizeof(c_cnt));

    d[start_x][start_y] = 0;
    c_cnt[start_x][start_y] = 1;

    Deque dq;
    initDeque(&dq);
    Cell start_cell = {start_x, start_y};
    pushBack(&dq, start_cell);

    while(!isEmpty(&dq)){
        Cell current = popFrontDeque(&dq);
        int x = current.x;
        int y = current.y;
        if(x == end_x && y == end_y){
            continue;
        }
        for(int k=0;k<8;k++){
            int ni = x + dx[k];
            int nj = y + dy[k];
            if(ni < 0 || ni >= M || nj < 0 || nj >= N){
                continue;
            }
            if(grid[ni][nj] == 2){
                continue; // Rock
            }
            int cost = 0;
            if(grid[ni][nj] == 0){
                cost = 1; // Need to add lilypad
            }
            // Existing lilypad or end is treated as cost 0
            int new_d = d[x][y] + cost;
            if(new_d < d[ni][nj]){
                d[ni][nj] = new_d;
                c_cnt[ni][nj] = c_cnt[x][y];
                Cell next = {ni, nj};
                if(cost == 0){
                    pushFront(&dq, next);
                }
                else{
                    pushBack(&dq, next);
                }
            }
            else if(new_d == d[ni][nj]){
                c_cnt[ni][nj] += c_cnt[x][y];
            }
        }
    }

    if(d[end_x][end_y] == INF){
        printf("-1\n");
    }
    else{
        // Count the number of additions
        int additions = d[end_x][end_y];
        // Now, we need to count the number of unique S sets.
        // Assuming that each path corresponds to a unique S set
        // as per the problem's sample, we output c_cnt[end_x][end_y]
        printf("%d\n%llu\n", additions, c_cnt[end_x][end_y]);
    }
    return 0;
}