#include <stdio.h>
#include <stdlib.h>

#define MAXM 30
#define MAXN 30
#define INF 1000000000

int M, N;
int pond[MAXM][MAXN];
int dp[MAXM][MAXN];

int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};

int bfs(int start_x, int start_y) {
    if (pond[start_x][start_y] == 2 || pond[start_x][start_y] == 3) return -1;

    dp[start_x][start_y] = 0;
    int queue[MAXM * MAXN][2];
    int front = 0, rear = 0;
    queue[rear][0] = start_x, queue[rear++][1] = start_y;

    while (front != rear) {
        int x = queue[front][0], y = queue[front++][1];
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < M && ny >= 0 && ny < N && pond[nx][ny] != 2) {
                if (dp[nx][ny] > dp[x][y] + 1) {
                    dp[nx][ny] = dp[x][y] + 1;
                    queue[rear][0] = nx, queue[rear++][1] = ny;
                }
            }
        }
    }

    return dp[M-1][N-1];
}

int main() {
    scanf("%d %d", &M, &N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &pond[i][j]);
            if (pond[i][j] == 3) {
                printf("%d\n", bfs(i, j));
                printf("%d\n", dp[M-1][N-1] == INF ? 0 : 1);
                return 0;
            } else if (pond[i][j] == 4) {
                pond[i][j] = 0;
            }
        }
    }

    int min_lilies = INF;
    long long ways = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (pond[i][j] == 0) {
                pond[i][j] = 1;
                int result = bfs(0, 0);
                if (result != -1 && result < min_lilies) {
                    min_lilies = result;
                    ways = 1;
                } else if (result != -1 && result == min_lilies) {
                    ways++;
                }
                pond[i][j] = 0;
            }
        }
    }

    if (min_lilies == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", min_lilies);
        printf("%lld\n", ways);
    }

    return 0;
}