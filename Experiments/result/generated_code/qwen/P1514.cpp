#include <stdio.h>
#include <stdlib.h>

#define MAXN 505
#define INF 1e9

int N, M;
int grid[MAXN][MAXN];
int visited[MAXN][MAXN];

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

void bfs(int x, int y) {
    if (x == 0 && y == 0) return; // Skip the starting point
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny] && grid[nx][ny] > grid[x][y]) {
            bfs(nx, ny);
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int has_factory = 0;
    for (int j = 0; j < M; j++) {
        if (grid[0][j] <= grid[N-1][j]) {
            printf("0\n%d\n", M); // If any city in the first row can't provide water to the last row, it's impossible
            return 0;
        }
    }

    for (int j = 0; j < M; j++) {
        if (grid[0][j] != INF) {
            bfs(0, j);
        }
    }

    for (int j = 0; j < M; j++) {
        if (!visited[N-1][j]) {
            printf("0\n%d\n", M); // If any city in the last row is not reachable, it's impossible
            return 0;
        }
    }

    printf("1\n%d\n", M); // All cities in the last row are reachable, so we need at least one factory
    return 0;
}