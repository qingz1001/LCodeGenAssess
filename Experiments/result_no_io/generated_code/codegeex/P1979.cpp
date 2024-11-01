#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 35
#define MAXQ 505
#define MAXE 10005
#define MAXV 1000005
#define INF 0x3f3f3f3f

int n, m, q;
int board[MAXN][MAXN];
int start_x, start_y, end_x, end_y;
int target_x, target_y;
int dist[MAXV];
int vis[MAXV];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

struct Node {
    int x, y;
    int step;
};

int encode(int x, int y, int z) {
    return (x << 16) | (y << 8) | z;
}

void decode(int code, int *x, int *y, int *z) {
    *z = code & 0xff;
    *y = (code >> 8) & 0xff;
    *x = (code >> 16) & 0xff;
}

int bfs() {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    int start = encode(start_x, start_y, encode(start_y, start_y, 0));
    dist[start] = 0;
    vis[start] = 1;
    struct Node queue[MAXV];
    int front = 0, rear = 0;
    queue[rear++] = {start_x, start_y, 0};
    while (front < rear) {
        struct Node cur = queue[front++];
        int x = cur.x, y = cur.y, step = cur.step;
        int cur_code = encode(x, y, encode(start_y, start_y, 0));
        if (x == target_x && y == target_y) {
            return step;
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > m || board[nx][ny] == 0) {
                continue;
            }
            int next_code = encode(nx, ny, encode(start_y, start_y, 0));
            if (vis[next_code]) {
                continue;
            }
            vis[next_code] = 1;
            dist[next_code] = step + 1;
            queue[rear++] = {nx, ny, step + 1};
        }
    }
    return -1;
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &board[i][j]);
        }
    }
    for (int i = 0; i < q; i++) {
        scanf("%d%d%d%d%d%d", &start_x, &start_y, &end_x, &end_y, &target_x, &target_y);
        int result = bfs();
        printf("%d\n", result);
    }
    return 0;
}