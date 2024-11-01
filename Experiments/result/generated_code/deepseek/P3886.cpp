#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 9

int N;
int grid[MAXN][MAXN];
int visited[MAXN][MAXN];
int max_survival_degree = INT_MIN;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int x, int y, int current_survival_degree) {
    if (current_survival_degree > max_survival_degree) {
        max_survival_degree = current_survival_degree;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < N && ny >= 0 && ny < N && !visited[nx][ny]) {
            visited[nx][ny] = 1;
            dfs(nx, ny, current_survival_degree + grid[nx][ny]);
            visited[nx][ny] = 0;
        }
    }
}

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = 1;
            dfs(i, j, grid[i][j]);
            visited[i][j] = 0;
        }
    }

    printf("%d\n", max_survival_degree);

    return 0;
}