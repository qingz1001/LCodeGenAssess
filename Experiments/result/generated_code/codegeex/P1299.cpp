#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 201

int paper[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void dfs(int x, int y) {
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < MAX_SIZE && ny >= 0 && ny < MAX_SIZE && !visited[nx][ny] && paper[nx][ny]) {
            dfs(nx, ny);
        }
    }
}

int count_holes(int n, int x1, int y1, int x2, int y2) {
    int min_x = min(x1, x2);
    int max_x = max(x1, x2);
    int min_y = min(y1, y2);
    int max_y = max(y1, y2);

    for (int i = min_x; i <= max_x; i++) {
        for (int j = min_y; j <= max_y; j++) {
            paper[i][j] = 0;
        }
    }

    int hole_count = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (paper[i][j] && !visited[i][j]) {
                dfs(i, j);
                hole_count++;
            }
        }
    }

    return hole_count;
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            paper[i][j] = 1;
            visited[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        int holes = count_holes(N, x1, y1, x2, y2);
        printf("%d\n", holes);
    }

    return 0;
}