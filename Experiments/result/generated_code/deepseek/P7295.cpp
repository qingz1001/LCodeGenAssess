#include <stdio.h>
#include <stdbool.h>

#define MAXN 1000
#define MAXM 1000
#define MAXQ 1000

char canvas[MAXN][MAXM];
int N, M, Q;
int x1[MAXQ], y1[MAXQ], x2[MAXQ], y2[MAXQ];
int component[MAXN][MAXM];
int component_size[MAXN * MAXM];
int component_count = 0;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int x, int y, char color) {
    if (x < 0 || x >= N || y < 0 || y >= M || canvas[x][y] != color || component[x][y] != -1) {
        return;
    }
    component[x][y] = component_count;
    component_size[component_count]++;
    for (int i = 0; i < 4; i++) {
        dfs(x + dx[i], y + dy[i], color);
    }
}

int main() {
    scanf("%d %d %d", &N, &M, &Q);
    for (int i = 0; i < N; i++) {
        scanf("%s", canvas[i]);
    }
    for (int i = 0; i < Q; i++) {
        scanf("%d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i]);
        x1[i]--; y1[i]--; x2[i]--; y2[i]--;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            component[i][j] = -1;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (component[i][j] == -1) {
                dfs(i, j, canvas[i][j]);
                component_count++;
            }
        }
    }

    for (int q = 0; q < Q; q++) {
        int count = 0;
        bool visited[component_count];
        for (int i = 0; i < component_count; i++) {
            visited[i] = false;
        }
        for (int i = x1[q]; i <= x2[q]; i++) {
            for (int j = y1[q]; j <= y2[q]; j++) {
                if (!visited[component[i][j]]) {
                    visited[component[i][j]] = true;
                    count++;
                }
            }
        }
        printf("%d\n", count);
    }

    return 0;
}