#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXN 500
#define MAXM 500

int N, M;
int grid[MAXN][MAXM];
bool visited[MAXN][MAXM];
bool canReach[MAXN][MAXM];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

typedef struct {
    int x, y;
} Point;

void dfs(int x, int y) {
    visited[x][y] = true;
    canReach[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny] && grid[nx][ny] < grid[x][y]) {
            dfs(nx, ny);
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

    // Mark cities that can be reached from the first row
    for (int j = 0; j < M; j++) {
        if (!visited[0][j]) {
            dfs(0, j);
        }
    }

    // Check if all cities in the last row can be reached
    int unreachableCount = 0;
    for (int j = 0; j < M; j++) {
        if (!canReach[N-1][j]) {
            unreachableCount++;
        }
    }

    if (unreachableCount > 0) {
        printf("0\n%d\n", unreachableCount);
        return 0;
    }

    // Calculate the minimum number of reservoirs needed
    int minReservoirs = 0;
    bool covered[MAXM] = {false};
    for (int j = 0; j < M; j++) {
        if (!covered[j]) {
            minReservoirs++;
            for (int k = j; k < M; k++) {
                if (canReach[N-1][k]) {
                    covered[k] = true;
                }
            }
        }
    }

    printf("1\n%d\n", minReservoirs);
    return 0;
}