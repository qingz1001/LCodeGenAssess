#include <stdio.h>
#include <string.h>

int n, m;
char map[25][25];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

struct node {
    int x, y, step;
};

int bfs(int sx, int sy) {
    int queue[4005][3];
    int front = 0, rear = 0;
    queue[rear][0] = sx;
    queue[rear][1] = sy;
    queue[rear++][2] = 0;
    int vis[25][25];
    memset(vis, 0, sizeof(vis));
    vis[sx][sy] = 1;
    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        int step = queue[front++][2];
        if (map[x][y] == 'D') {
            return step;
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny] && map[nx][ny] != 'X') {
                queue[rear][0] = nx;
                queue[rear][1] = ny;
                queue[rear++][2] = step + 1;
                vis[nx][ny] = 1;
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", map[i] + 1);
    }
    int ans = -1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (map[i][j] == '.') {
                int t = bfs(i, j);
                if (t == -1) {
                    printf("impossible\n");
                    return 0;
                }
                if (ans == -1 || t < ans) {
                    ans = t;
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}