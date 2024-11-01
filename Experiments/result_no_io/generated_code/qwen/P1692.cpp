#include <stdio.h>
#include <stdlib.h>

#define MAXN 105
#define MAXM 3005

int n, m;
int graph[MAXN][MAXN];
int visited[MAXN];
int inQueue[MAXN];
int queue[MAXM * 2];
int front, rear;

void bfs(int start) {
    front = rear = 0;
    queue[rear++] = start;
    inQueue[start] = 1;
    while (front != rear) {
        int u = queue[front++];
        for (int v = 1; v <= n; v++) {
            if (graph[u][v] && !visited[v]) {
                visited[v] = 1;
                if (!inQueue[v]) {
                    queue[rear++] = v;
                    inQueue[v] = 1;
                }
            }
        }
    }
}

void dfs(int start, int *result) {
    visited[start] = 1;
    result[start] = 1;
    for (int v = 1; v <= n; v++) {
        if (graph[start][v] && !visited[v]) {
            dfs(v, result);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    int result[n + 1];
    for (int i = 1; i <= n; i++) {
        result[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            bfs(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, result);
        }
    }

    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (result[i]) {
            count++;
        }
    }

    printf("%d\n", count);
    for (int i = 1; i <= n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}