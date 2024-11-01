#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_N 50
#define MAX_M 50
#define INF INT_MAX

int N, M;
int map[MAX_N][MAX_M];
int dist[MAX_N][MAX_M][4];
bool visited[MAX_N][MAX_M][4];

int dx[] = {0, 1, 0, -1}; // E, S, W, N
int dy[] = {1, 0, -1, 0};

typedef struct {
    int x, y, dir, time;
} State;

State queue[MAX_N * MAX_M * 4];
int front, rear;

void enqueue(State s) {
    queue[rear++] = s;
}

State dequeue() {
    return queue[front++];
}

bool isEmpty() {
    return front == rear;
}

bool isValid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M && map[x][y] == 0;
}

bool canMove(int x, int y) {
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (!isValid(i, j)) return false;
        }
    }
    return true;
}

int bfs(int sx, int sy, int sdir, int ex, int ey) {
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, false, sizeof(visited));
    
    front = rear = 0;
    enqueue((State){sx, sy, sdir, 0});
    dist[sx][sy][sdir] = 0;
    visited[sx][sy][sdir] = true;
    
    while (!isEmpty()) {
        State cur = dequeue();
        
        if (cur.x == ex && cur.y == ey) {
            return cur.time;
        }
        
        // Turn left or right
        for (int i = -1; i <= 1; i += 2) {
            int ndir = (cur.dir + i + 4) % 4;
            if (!visited[cur.x][cur.y][ndir]) {
                visited[cur.x][cur.y][ndir] = true;
                dist[cur.x][cur.y][ndir] = cur.time + 1;
                enqueue((State){cur.x, cur.y, ndir, cur.time + 1});
            }
        }
        
        // Move forward
        for (int step = 1; step <= 3; step++) {
            int nx = cur.x + dx[cur.dir] * step;
            int ny = cur.y + dy[cur.dir] * step;
            
            if (!canMove(nx, ny)) break;
            
            if (!visited[nx][ny][cur.dir]) {
                visited[nx][ny][cur.dir] = true;
                dist[nx][ny][cur.dir] = cur.time + 1;
                enqueue((State){nx, ny, cur.dir, cur.time + 1});
            }
        }
    }
    
    return -1;
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &map[i][j]);
        }
    }
    
    int sx, sy, ex, ey;
    char dir;
    scanf("%d %d %d %d %c", &sx, &sy, &ex, &ey, &dir);
    
    int sdir;
    if (dir == 'E') sdir = 0;
    else if (dir == 'S') sdir = 1;
    else if (dir == 'W') sdir = 2;
    else sdir = 3;
    
    int result = bfs(sx, sy, sdir, ex, ey);
    printf("%d\n", result);
    
    return 0;
}