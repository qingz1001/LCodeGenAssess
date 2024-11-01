#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50
#define MAX_M 50
#define INF 0x3f3f3f3f

typedef struct {
    int x, y;
    char dir;
} Robot;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
char dirc[] = {'W', 'E', 'N', 'S'};

int is_valid(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int min_time(char grid[MAX_N][MAX_M], int n, int m, int sx, int sy, char sdir, int ex, int ey) {
    int dist[MAX_N][MAX_M][4];
    memset(dist, INF, sizeof(dist));
    Robot q[MAX_N * MAX_M];
    int front = 0, rear = 0;
    
    for (int i = 0; i < 4; i++) {
        if (grid[sx][sy] == '0') {
            dist[sx][sy][i] = 0;
            q[rear++] = (Robot){sx, sy, dirc[i]};
        }
    }
    
    while (front != rear) {
        Robot r = q[front++];
        int cx = r.x, cy = r.y, cd = r.dir - 'N';
        
        for (int i = 0; i <= 3; i++) {
            int nx = cx + dx[(cd + i) % 4];
            int ny = cy + dy[(cd + i) % 4];
            int nd = (cd + i) % 4;
            
            if (is_valid(nx, ny, n, m) && grid[nx][ny] == '0' && dist[nx][ny][nd] > dist[cx][cy][cd] + 1) {
                dist[nx][ny][nd] = dist[cx][cy][cd] + 1;
                q[rear++] = (Robot){nx, ny, dirc[nd]};
            }
        }
        
        for (int step = 2; step <= 3; step++) {
            int nx = cx + dx[cd] * step;
            int ny = cy + dy[cd] * step;
            
            if (is_valid(nx, ny, n, m) && grid[nx][ny] == '0' && dist[nx][ny][cd] > dist[cx][cy][cd] + step) {
                dist[nx][ny][cd] = dist[cx][cy][cd] + step;
                q[rear++] = (Robot){nx, ny, dirc[cd]};
            }
        }
    }
    
    int ans = INF;
    for (int i = 0; i < 4; i++) {
        ans = fmin(ans, dist[ex][ey][i]);
    }
    
    return ans == INF ? -1 : ans;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[MAX_N][MAX_M];
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    
    int sx, sy, ex, ey;
    char sdir;
    scanf("%d %d %d %d %c", &sx, &sy, &ex, &ey, &sdir);
    
    printf("%d\n", min_time(grid, n, m, sx, sy, sdir, ex, ey));
    
    return 0;
}