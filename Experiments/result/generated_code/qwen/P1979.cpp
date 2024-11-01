#include <stdio.h>
#include <stdlib.h>

#define MAXN 30
#define INF 1e9

int n, m, q;
int board[MAXN][MAXN];
int ex[MAXN], ey[MAXN], sx[MAXN], sy[MAXN], tx[MAXN], ty[MAXN];

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && board[x][y] != 0;
}

int bfs(int sx, int sy, int tx, int ty, int blank_x, int blank_y) {
    if (sx == tx && sy == ty) return 0;

    int dist[MAXN][MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dist[i][j] = INF;
        }
    }

    dist[sx][sy] = 0;
    int queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = sx * m + sy;

    while (front < rear) {
        int u = queue[front++];
        int ux = u / m, uy = u % m;

        for (int k = 0; k < 4; k++) {
            int vx = ux + dx[k], vy = uy + dy[k];
            if (!is_valid(vx, vy)) continue;
            if (dist[vx][vy] != INF) continue;
            dist[vx][vy] = dist[ux][uy] + 1;
            queue[rear++] = vx * m + vy;
        }
    }

    if (dist[tx][ty] == INF) return -1;

    int min_moves = dist[tx][ty];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 1) {
                int d = abs(i - blank_x) + abs(j - blank_y);
                if (d < min_moves) min_moves = d;
            }
        }
    }

    return min_moves + dist[tx][ty];
}

int main() {
    scanf("%d %d %d", &n, &m, &q);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    for (int i = 0; i < q; i++) {
        scanf("%d %d %d %d %d %d", &ex[i], &ey[i], &sx[i], &sy[i], &tx[i], &ty[i]);
        ex[i]--;
        ey[i]--;
        sx[i]--;
        sy[i]--;
        tx[i]--;
        ty[i]--;
    }

    for (int i = 0; i < q; i++) {
        int ans = bfs(sx[i], sy[i], tx[i], ty[i], ex[i], ey[i]);
        printf("%d\n", ans);
    }

    return 0;
}