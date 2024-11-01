#include <stdio.h>
#include <string.h>

#define MAXN 101
#define MAXM 10001

int n, m;
int maze[MAXN][MAXN];
int visited[MAXM][MAXM];

struct Point {
    int x, y, steps;
    int direction;
};

int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int isValid(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

void bfs() {
    struct Point queue[MAXM * MAXM];
    int front = 0, rear = 0;
    
    queue[rear++] = {1, 1, 0, -1};
    visited[1][1] = 1;
    
    while (front < rear) {
        struct Point current = queue[front++];
        
        if (current.x == n && current.y == m) {
            printf("%d\n", current.steps);
            return;
        }
        
        for (int i = 0; i < 8; i++) {
            if (i == current.direction) continue;
            
            int nx = current.x + dx[i] * maze[current.x][current.y];
            int ny = current.y + dy[i] * maze[current.x][current.y];
            
            if (isValid(nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = 1;
                queue[rear++] = {nx, ny, current.steps + 1, i};
            }
        }
    }
    
    printf("NEVER\n");
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    
    memset(visited, 0, sizeof(visited));
    bfs();
    
    return 0;
}