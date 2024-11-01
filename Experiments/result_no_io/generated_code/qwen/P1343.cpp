#include <stdio.h>
#include <stdlib.h>

#define MAXN 205
#define INF 0x3f3f3f3f

int n, m, x;
int graph[MAXN][MAXN];
int capacity[MAXN][MAXN];

void bfs(int start, int end) {
    int queue[MAXN], front = 0, rear = 0;
    int visited[MAXN] = {0};
    int flow = 0;

    while (front != rear) {
        int u = queue[front++];
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && graph[u][v] > 0 && capacity[u][v] > 0) {
                queue[rear++] = v;
                visited[v] = 1;
                graph[u][v]--;
                graph[v][u]++;
                capacity[u][v]--;
                capacity[v][u]++;
                flow += capacity[u][v];
            }
        }
    }

    printf("%d %d\n", flow, (x + flow - 1) / flow);
}

int main() {
    scanf("%d %d %d", &n, &m, &x);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
            capacity[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        graph[a][b] += c;
        capacity[a][b] += c;
    }

    bfs(1, n);

    return 0;
}