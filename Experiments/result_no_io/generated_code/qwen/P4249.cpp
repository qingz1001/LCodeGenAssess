#include <stdio.h>
#include <stdlib.h>

#define MAXN 105

int N;
int graph[MAXN][MAXN];
int result[MAXN][MAXN];

void dfs(int u, int v, int win) {
    if (graph[u][v] == 2) {
        graph[u][v] = win;
        graph[v][u] = !win;
        result[u][v] = win;
        result[v][u] = !win;
        for (int i = 0; i < N; i++) {
            if (graph[u][i] == 2 && graph[i][v] == 2) {
                dfs(i, u, !win);
                dfs(i, v, win);
            }
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

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (graph[i][j] == 2) {
                dfs(i, j, 1);
            }
        }
    }

    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (result[i][j] != graph[i][j]) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}