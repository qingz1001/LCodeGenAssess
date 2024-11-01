#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500

int N;
int field[MAXN][MAXN];
int visited[MAXN][MAXN];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int dfs(int x, int y, int max_diff) {
    if (visited[x][y]) return 0;
    visited[x][y] = 1;
    int count = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < N && ny >= 0 && ny < N && !visited[nx][ny] && abs(field[nx][ny] - field[x][y]) <= max_diff) {
            count += dfs(nx, ny, max_diff);
        }
    }
    return count;
}

int can_visit_half(int max_diff) {
    int half = (N * N + 1) / 2;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < N; l++) {
                    visited[k][l] = 0;
                }
            }
            if (dfs(i, j, max_diff) >= half) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &field[i][j]);
        }
    }

    int left = 0, right = 1000000;
    while (left < right) {
        int mid = (left + right) / 2;
        if (can_visit_half(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);
    return 0;
}