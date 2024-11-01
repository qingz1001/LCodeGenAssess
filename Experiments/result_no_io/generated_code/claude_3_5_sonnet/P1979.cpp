#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 30
#define MAX_M 30
#define INF 0x3f3f3f3f

int n, m, q;
int board[MAX_N][MAX_M];
int dist[MAX_N][MAX_M];
bool visited[MAX_N][MAX_M];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

typedef struct {
    int x, y;
} Point;

Point queue[MAX_N * MAX_M];
int front, rear;

void enqueue(int x, int y) {
    queue[rear].x = x;
    queue[rear].y = y;
    rear++;
}

Point dequeue() {
    return queue[front++];
}

bool is_empty() {
    return front == rear;
}

void bfs(int ex, int ey) {
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, false, sizeof(visited));
    
    front = rear = 0;
    enqueue(ex, ey);
    dist[ex][ey] = 0;
    visited[ex][ey] = true;
    
    while (!is_empty()) {
        Point curr = dequeue();
        int x = curr.x, y = curr.y;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && board[nx][ny] == 1 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                dist[nx][ny] = dist[x][y] + 1;
                enqueue(nx, ny);
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &board[i][j]);
        }
    }
    
    while (q--) {
        int ex, ey, sx, sy, tx, ty;
        scanf("%d %d %d %d %d %d", &ex, &ey, &sx, &sy, &tx, &ty);
        
        bfs(ex, ey);
        
        if (!visited[sx][sy] || !visited[tx][ty]) {
            printf("-1\n");
        } else {
            int result = dist[sx][sy] + dist[tx][ty];
            printf("%d\n", result);
        }
    }
    
    return 0;
}