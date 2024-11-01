#include <stdio.h>

#define MAXN 105

int N;
int graph[MAXN][MAXN];
int result[MAXN][MAXN];

void dfs(int u, int color) {
    for (int v = 0; v < N; v++) {
        if (graph[u][v] == 2) {
            graph[u][v] = color;
            graph[v][u] = 1 - color;
            dfs(v, 1 - color);
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int count = 0;
    for (int i = 0; i < N; i++) {
        if (graph[i][i] != 0) continue;
        if (graph[i][i] == 0) {
            dfs(i, 1);
            count++;
        }
    }

    printf("%d\n", count);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (graph[i][j] == 2) {
                if (result[i][j] == 0) {
                    result[i][j] = 1;
                    result[j][i] = 0;
                } else {
                    result[i][j] = 0;
                    result[j][i] = 1;
                }
            } else {
                result[i][j] = graph[i][j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}