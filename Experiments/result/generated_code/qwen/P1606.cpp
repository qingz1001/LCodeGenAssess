#include <stdio.h>
#include <stdlib.h>

#define MAXM 30
#define MAXN 30
#define INF 1e9

int M, N;
int grid[MAXM][MAXN];
int dp[MAXM][MAXN];

int dx[] = {1, -1, 2, -2, 2, -2, 1, -1};
int dy[] = {2, 2, 1, 1, -1, -1, -2, -2};

int bfs(int start_x, int start_y) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = INF;
        }
    }
    dp[start_x][start_y] = 0;
    int queue[MAXM * MAXN][2];
    int front = 0, rear = 0;
    queue[rear][0] = start_x;
    queue[rear++][1] = start_y;

    while (front != rear) {
        int x = queue[front][0];
        int y = queue[front++][1];
        if (grid[x][y] == 4) break;
        for (int k = 0; k < 8; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx >= 0 && nx < M && ny >= 0 && ny < N && grid[nx][ny] != 2 && dp[nx][ny] > dp[x][y] + 1) {
                dp[nx][ny] = dp[x][y] + 1;
                queue[rear][0] = nx;
                queue[rear++][1] = ny;
            }
        }
    }

    return dp[grid[0][0]][0];
}

void dfs(int x, int y, int add_count, long long &ways) {
    if (x < 0 || x >= M || y < 0 || y >= N || grid[x][y] == 2 || dp[x][y] != add_count) return;
    if (dp[x][y] == add_count) {
        if (grid[x][y] == 4) {
            ways++;
            return;
        }
        grid[x][y] = 1;
        for (int k = 0; k < 8; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            dfs(nx, ny, add_count, ways);
        }
        grid[x][y] = 0;
    }
}

int main() {
    scanf("%d %d", &M, &N);
    int start_x, start_y, end_x, end_y;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
            if (grid[i][j] == 3) {
                start_x = i;
                start_y = j;
            } else if (grid[i][j] == 4) {
                end_x = i;
                end_y = j;
            }
        }
    }

    int min_add = bfs(start_x, start_y);
    if (min_add == INF) {
        printf("-1\n");
        return 0;
    }

    long long ways = 0;
    dfs(end_x, end_y, min_add, ways);

    printf("%d\n%lld\n", min_add, ways);
    return 0;
}