#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 35
#define MAXM 35
#define INF 0x3f3f3f3f

int n, m, q;
int board[MAXN][MAXM];
int dist[MAXN][MAXM];
bool vis[MAXN][MAXM];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

typedef struct {
    int x, y;
} Point;

Point queue[MAXN * MAXM];

bool is_valid(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m && board[x][y] == 1;
}

int bfs(int sx, int sy, int tx, int ty) {
    memset(vis, 0, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));
    
    int front = 0, rear = 0;
    queue[rear++] = (Point){sx, sy};
    vis[sx][sy] = true;
    dist[sx][sy] = 0;
    
    while (front < rear) {
        Point cur = queue[front++];
        
        if (cur.x == tx && cur.y == ty) {
            return dist[tx][ty];
        }
        
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            
            if (is_valid(nx, ny) && !vis[nx][ny]) {
                vis[nx][ny] = true;
                dist[nx][ny] = dist[cur.x][cur.y] + 1;
                queue[rear++] = (Point){nx, ny};
            }
        }
    }
    
    return -1;
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
        
        if (board[sx][sy] == 0 || board[tx][ty] == 0) {
            printf("-1\n");
            continue;
        }
        
        int empty_to_start = bfs(ex, ey, sx, sy);
        if (empty_to_start == -1) {
            printf("-1\n");
            continue;
        }
        
        int start_to_target = bfs(sx, sy, tx, ty);
        if (start_to_target == -1) {
            printf("-1\n");
            continue;
        }
        
        printf("%d\n", empty_to_start + start_to_target);
    }
    
    return 0;
}