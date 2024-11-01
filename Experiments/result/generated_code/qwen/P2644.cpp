#include <stdio.h>
#include <stdlib.h>

#define MAX_M 30
#define MAX_N 30
#define INF 999999999

int M, N, P;
int grid[MAX_M][MAX_N];
int startX, startY, endX, endY;

typedef struct {
    int x, y, steps, gold;
} State;

void bfs(int startSteps, int startGold) {
    int queue[MAX_M * MAX_N * 2][4];
    int front = 0, rear = 0;
    queue[rear][0] = startX; queue[rear][1] = startY; queue[rear][2] = startSteps; queue[rear][3] = startGold; rear++;
    int minSteps = INF, maxGold = -1;
    while (front != rear) {
        int x = queue[front][0], y = queue[front][1], steps = queue[front][2], gold = queue[front][3]; front++;
        if (x == endX && y == endY) {
            if (steps < minSteps || (steps == minSteps && gold > maxGold)) {
                minSteps = steps;
                maxGold = gold;
            }
            continue;
        }
        int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
        int dy[] = {1, -1, 2, -2, 2, -2, 1, -1};
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
                if (grid[nx][ny] == 1 || grid[nx][ny] == 4) {
                    if (steps + 1 <= P) {
                        queue[rear][0] = nx; queue[rear][1] = ny; queue[rear][2] = steps + 1; queue[rear][3] = gold; rear++;
                    }
                } else if (grid[nx][ny] == 5) {
                    if (steps + 2 <= P) {
                        queue[rear][0] = nx; queue[rear][1] = ny; queue[rear][2] = steps + 2; queue[rear][3] = gold + 1; rear++;
                    }
                }
            }
        }
    }
    printf("%d %d\n", minSteps, minSteps == INF ? 0 : 1);
    printf("%d %d\n", maxGold, maxGold == -1 ? 0 : 1);
}

int main() {
    scanf("%d %d %d", &P, &M, &N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
            if (grid[i][j] == 3) {
                startX = i; startY = j;
            } else if (grid[i][j] == 4) {
                endX = i; endY = j;
            }
        }
    }
    bfs(0, 0);
    return 0;
}