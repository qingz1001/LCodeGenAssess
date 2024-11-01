#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 30
#define MAX_N 30
#define INF 0x3f3f3f3f

typedef struct {
    int x, y;
} Point;

typedef struct {
    int cost;
    int platinum;
    int ways;
} State;

int M, N, P;
int grid[MAX_M][MAX_N];
Point start, end;
int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};
State dp[MAX_M][MAX_N][MAX_P + 1];

void initialize() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k <= P; k++) {
                dp[i][j][k].cost = INF;
                dp[i][j][k].platinum = -1;
                dp[i][j][k].ways = 0;
            }
        }
    }
}

void bfs() {
    Point queue[MAX_M * MAX_N * (P + 1)];
    int front = 0, rear = 0;
    queue[rear++] = start;
    dp[start.x][start.y][0].cost = 0;
    dp[start.x][start.y][0].ways = 1;

    while (front < rear) {
        Point current = queue[front++];
        int cost = dp[current.x][current.y][0].cost;
        int ways = dp[current.x][current.y][0].ways;

        for (int i = 0; i < 8; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
                int new_cost = cost + (grid[nx][ny] == 5 ? 2 : 1);
                int new_platinum = (grid[nx][ny] == 5 ? 1 : 0);

                if (new_cost <= P && new_cost < dp[nx][ny][new_cost].cost) {
                    dp[nx][ny][new_cost].cost = new_cost;
                    dp[nx][ny][new_cost].platinum = new_platinum;
                    dp[nx][ny][new_cost].ways = ways;
                    queue[rear++] = (Point){nx, ny};
                } else if (new_cost <= P && new_cost == dp[nx][ny][new_cost].cost) {
                    dp[nx][ny][new_cost].ways += ways;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &P, &M, &N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
            if (grid[i][j] == 3) start = (Point){i, j};
            if (grid[i][j] == 4) end = (Point){i, j};
        }
    }

    initialize();
    bfs();

    int min_cost = INF, ways_S = 0;
    for (int k = 0; k <= P; k++) {
        if (dp[end.x][end.y][k].cost < min_cost) {
            min_cost = dp[end.x][end.y][k].cost;
            ways_S = dp[end.x][end.y][k].ways;
        } else if (dp[end.x][end.y][k].cost == min_cost) {
            ways_S += dp[end.x][end.y][k].ways;
        }
    }

    if (min_cost == INF) {
        printf("-1\n");
        return 0;
    }

    int max_platinum = -1, ways_G = 0;
    for (int k = 0; k <= P; k++) {
        if (dp[end.x][end.y][k].cost == min_cost) {
            if (dp[end.x][end.y][k].platinum > max_platinum) {
                max_platinum = dp[end.x][end.y][k].platinum;
                ways_G = dp[end.x][end.y][k].ways;
            } else if (dp[end.x][end.y][k].platinum == max_platinum) {
                ways_G += dp[end.x][end.y][k].ways;
            }
        }
    }

    printf("%d %d\n", min_cost, ways_S);
    if (max_platinum == -1) {
        printf("-1\n");
    } else {
        printf("%d %d\n", max_platinum, ways_G);
    }

    return 0;
}