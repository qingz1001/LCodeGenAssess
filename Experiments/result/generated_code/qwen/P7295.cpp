#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 1000

int N, M, Q;
char canvas[MAX_N][MAX_M + 1];
int visited[MAX_N][MAX_M];

void dfs(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M || visited[x][y] || canvas[x][y] == '.') return;
    visited[x][y] = 1;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int minPaintingSteps(char targetColor) {
    int steps = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!visited[i][j] && canvas[i][j] == targetColor) {
                steps++;
                dfs(i, j);
            }
        }
    }
    return steps;
}

int main() {
    scanf("%d %d %d", &N, &M, &Q);
    for (int i = 0; i < N; i++) {
        scanf("%s", canvas[i]);
    }

    for (int q = 0; q < Q; q++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        x1--; y1--; x2--; y2--;

        char targetColor = canvas[x1][y1];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                visited[i][j] = 0;
            }
        }

        int count = 0;
        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                if (canvas[i][j] != targetColor) {
                    count++;
                } else {
                    canvas[i][j] = '.';
                }
            }
        }

        printf("%d\n", count + minPaintingSteps(targetColor));
    }

    return 0;
}