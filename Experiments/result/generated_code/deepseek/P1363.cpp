#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 1500
#define MAXM 1500

char maze[MAXN][MAXM];
bool visited[MAXN][MAXM][3][3];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int N, M;

typedef struct {
    int x, y, px, py;
} State;

bool bfs(int sx, int sy) {
    State queue[MAXN * MAXM * 9];
    int front = 0, rear = 0;
    queue[rear++] = (State){sx, sy, sx % N, sy % M};
    memset(visited, false, sizeof(visited));
    visited[sx % N][sy % M][sx / N + 1][sy / M + 1] = true;

    while (front < rear) {
        State cur = queue[front++];
        int cx = cur.x, cy = cur.y, px = cur.px, py = cur.py;

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i], ny = cy + dy[i];
            int npx = nx % N, npy = ny % M;
            int nbx = nx / N, nby = ny / M;

            if (nx < 0 || ny < 0 || nx >= N * 3 || ny >= M * 3) continue;
            if (maze[npx][npy] == '#') continue;
            if (visited[npx][npy][nbx + 1][nby + 1]) continue;

            if (nbx != nx / N || nby != ny / M) {
                return true;
            }

            visited[npx][npy][nbx + 1][nby + 1] = true;
            queue[rear++] = (State){nx, ny, npx, npy};
        }
    }

    return false;
}

int main() {
    while (scanf("%d %d", &N, &M) != EOF) {
        int sx = -1, sy = -1;
        for (int i = 0; i < N; i++) {
            scanf("%s", maze[i]);
            for (int j = 0; j < M; j++) {
                if (maze[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
            }
        }

        if (sx == -1 || sy == -1) {
            printf("No\n");
            continue;
        }

        if (bfs(sx, sy)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}