#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXK 10

int N, K, A, B, C;
int grid[MAXN][MAXN];
int dp[MAXN][MAXN][MAXK + 1];

typedef struct {
    int x, y, fuel;
} State;

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d %d %d %d", &N, &K, &A, &B, &C);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
            for (int k = 0; k <= K; k++) {
                dp[i][j][k] = INT_MAX;
            }
        }
    }

    dp[0][0][K] = 0;
    State queue[MAXN * MAXN * (MAXK + 1)];
    int front = 0, rear = 0;
    queue[rear++] = (State){0, 0, K};

    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    while (front < rear) {
        State current = queue[front++];
        int x = current.x, y = current.y, fuel = current.fuel;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;

            int cost = (i < 2) ? 0 : B; // 0 and 1 are right and down, no cost; 2 and 3 are left and up, cost B
            if (fuel > 0 && dp[nx][ny][fuel - 1] > dp[x][y][fuel] + cost) {
                dp[nx][ny][fuel - 1] = dp[x][y][fuel] + cost;
                queue[rear++] = (State){nx, ny, fuel - 1};
            }
        }

        if (grid[x][y] == 1 && dp[x][y][K] > dp[x][y][fuel] + A) {
            dp[x][y][K] = dp[x][y][fuel] + A;
            queue[rear++] = (State){x, y, K};
        }

        if (dp[x][y][K] > dp[x][y][fuel] + C) {
            dp[x][y][K] = dp[x][y][fuel] + C;
            queue[rear++] = (State){x, y, K};
        }
    }

    int result = INT_MAX;
    for (int k = 0; k <= K; k++) {
        result = min(result, dp[N-1][N-1][k]);
    }

    printf("%d\n", result);
    return 0;
}