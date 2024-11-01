#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define INF 0x3f3f3f3f

int n, m;
int graph[MAXN][MAXN];
int degree[MAXN];

void bfs(int start) {
    int queue[MAXN];
    int front = 0, rear = 0;
    queue[rear++] = start;
    while (front != rear) {
        int u = queue[front++];
        for (int v = 1; v <= n; v++) {
            if (graph[u][v] && !degree[v]) {
                degree[v]--;
                if (!degree[v]) {
                    queue[rear++] = v;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int b, e;
        scanf("%d %d", &b, &e);
        graph[b][e] = 1;
        degree[e]++;
    }

    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!degree[i]) {
            bfs(i);
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}