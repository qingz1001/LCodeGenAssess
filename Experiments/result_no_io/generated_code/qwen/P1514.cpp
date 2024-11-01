#include <stdio.h>
#include <stdlib.h>

#define MAXN 505
#define MAXM 505

int N, M;
int height[MAXN][MAXM];
int visited[MAXN][MAXM];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void bfs(int x, int y) {
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny] && height[nx][ny] < height[x][y]) {
            bfs(nx, ny);
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &height[i][j]);
        }
    }

    int factory_count = 0;
    int impossible_count = 0;

    // Check the first row for factories
    for (int j = 0; j < M; j++) {
        if (!visited[0][j] && height[0][j] == 1) {
            factory_count++;
            bfs(0, j);
        }
    }

    // Check if all cities in the last row are reachable
    for (int j = 0; j < M; j++) {
        if (!visited[N-1][j]) {
            impossible_count++;
        }
    }

    if (impossible_count > 0) {
        printf("0\n%d\n", impossible_count);
    } else {
        printf("1\n%d\n", factory_count);
    }

    return 0;
}