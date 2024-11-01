#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100
#define INF INT_MAX

char grid[MAX_N][MAX_N];
int dist[MAX_N][MAX_N][4];
int N;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

typedef struct {
    int x, y, dir, turns;
} State;

State queue[MAX_N * MAX_N * 4];
int front, rear;

void enqueue(int x, int y, int dir, int turns) {
    queue[rear++] = (State){x, y, dir, turns};
}

State dequeue() {
    return queue[front++];
}

int bfs(int sx, int sy, int ex, int ey) {
    memset(dist, 0x3f, sizeof(dist));
    front = rear = 0;
    
    for (int i = 0; i < 4; i++) {
        dist[sx][sy][i] = 0;
        enqueue(sx, sy, i, 0);
    }
    
    while (front < rear) {
        State cur = dequeue();
        
        if (cur.x == ex && cur.y == ey) {
            return cur.turns;
        }
        
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            int nturns = cur.turns + (i != cur.dir);
            
            if (nx >= 0 && nx < N && ny >= 0 && ny < N && grid[nx][ny] != 'x') {
                if (nturns < dist[nx][ny][i]) {
                    dist[nx][ny][i] = nturns;
                    enqueue(nx, ny, i, nturns);
                }
            }
        }
    }
    
    return -1;
}

int main() {
    int sx, sy, ex, ey;
    
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf(" %c", &grid[i][j]);
            if (grid[i][j] == 'A') {
                sx = i; sy = j;
            } else if (grid[i][j] == 'B') {
                ex = i; ey = j;
            }
        }
    }
    
    int result = bfs(sx, sy, ex, ey);
    printf("%d\n", result);
    
    return 0;
}