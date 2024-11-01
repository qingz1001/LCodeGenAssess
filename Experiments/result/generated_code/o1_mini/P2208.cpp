#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 501
#define MAXM 501
#define MAX_QUEUE 500 * 500 * 2
#define INF 1000000000

typedef struct {
    int x, y, gravity;
} State;

int N, M;
char grid[MAXN][MAXM];
int visited[MAXN][MAXM][2];
State queue_q[MAX_QUEUE];
int head = 0, tail = 0;

int start_x, start_y, end_x, end_y;

// Directions: left and right
int dx[2] = {0, 0};
int dy[2] = {-1, 1};

// Enqueue function
void enqueue(State s) {
    if (tail < MAX_QUEUE) {
        queue_q[tail++] = s;
    }
}

// Dequeue function
State dequeue() {
    return queue_q[head++];
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N;i++){
        scanf("%s", grid[i]);
        for(int j=0;j<M;j++){
            if(grid[i][j] == 'C'){
                start_x = i;
                start_y = j+1;
            }
            if(grid[i][j] == 'D'){
                end_x = i;
                end_y = j+1;
            }
        }
    }
    // Initialize BFS
    memset(visited, 0, sizeof(visited));
    State start;
    start.x = start_x;
    start.y = start_y;
    start.gravity = 0; // 0 = down, 1 = up
    enqueue(start);
    visited[start.x][start.y][start.gravity] = 1;
    int flips = 0;
    while(head < tail){
        int size = tail - head;
        for(int i=0;i<size;i++){
            State current = dequeue();
            // Simulate fall
            int x = current.x;
            int y = current.y;
            int gravity = current.gravity;
            while(1){
                int nx = x + (gravity == 0 ? 1 : -1);
                if(nx < 1 || nx > N){
                    x = -1;
                    break;
                }
                if(grid[nx][y-1] == '#'){
                    break;
                }
                x = nx;
            }
            if(x == -1) continue;
            if(x == end_x && y == end_y){
                printf("%d", flips);
                return 0;
            }
            // Try moving left and right
            for(int d=0;d<2;d++){
                int ny = y + dy[d];
                if(ny <1 || ny > M) continue;
                if(grid[x][ny-1] == '#') continue;
                if(!visited[x][ny][gravity]){
                    visited[x][ny][gravity] = 1;
                    State next;
                    next.x = x;
                    next.y = ny;
                    next.gravity = gravity;
                    enqueue(next);
                }
            }
            // Try flipping gravity
            int new_gravity = gravity ^ 1;
            if(!visited[x][y][new_gravity]){
                visited[x][y][new_gravity] = 1;
                State next;
                next.x = x;
                next.y = y;
                next.gravity = new_gravity;
                enqueue(next);
            }
        }
        flips++;
    }
    printf("-1");
    return 0;
}