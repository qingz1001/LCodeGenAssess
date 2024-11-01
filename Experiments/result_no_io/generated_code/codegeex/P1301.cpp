#include <stdio.h>
#include <string.h>

#define MAXN 105
#define MAXM 105
#define MAXSTEP 1000005

int N, M;
int magic[MAXN][MAXM];
int visited[MAXN][MAXM][8][MAXSTEP];
int dir[8][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
int step;

int isValid(int x, int y) {
    return x >= 1 && x <= N && y >= 1 && y <= M;
}

int bfs(int x, int y) {
    memset(visited, 0, sizeof(visited));
    visited[x][y][step][0] = 1;
    int queue[MAXN*MAXM*8][3];
    int front = 0, rear = 0;
    queue[rear][0] = x;
    queue[rear][1] = y;
    queue[rear++][2] = step;

    while (front < rear) {
        int cx = queue[front][0];
        int cy = queue[front][1];
        int cstep = queue[front++][2];

        if (cx == N && cy == M) {
            return cstep;
        }

        for (int i = 0; i < 8; i++) {
            if (i == (cstep % 8)) continue; // 不能连续两次相同方向跳跃
            int nx = cx + dir[i][0] * magic[cx][cy];
            int ny = cy + dir[i][1] * magic[cx][cy];
            if (isValid(nx, ny) && !visited[nx][ny][i][cstep + 1]) {
                visited[nx][ny][i][cstep + 1] = 1;
                queue[rear][0] = nx;
                queue[rear][1] = ny;
                queue[rear++][2] = (cstep + 1) % 8;
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%d", &magic[i][j]);
        }
    }

    int result = bfs(1, 1);
    if (result == -1) {
        printf("NEVER\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}