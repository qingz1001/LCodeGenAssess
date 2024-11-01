#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 31
#define MAXQ 501
#define MAXV 901
#define MAXE 27001
#define MAXH 901

int n, m, q;
int board[MAXN][MAXN];
int dist[MAXV][MAXV];
int sx, sy, tx, ty, ex, ey;

struct Edge {
    int v, w, next;
} edge[MAXE];

int head[MAXV], tot;

void addEdge(int u, int v, int w) {
    edge[tot].v = v;
    edge[tot].w = w;
    edge[tot].next = head[u];
    head[u] = tot++;
}

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void bfs(int start) {
    int visited[MAXV] = {0};
    int queue[MAXV], front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;
    dist[start][start] = 0;

    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v, w = edge[i].w;
            if (visited[v]) continue;
            visited[v] = 1;
            dist[start][v] = dist[start][u] + w;
            queue[rear++] = v;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    memset(head, -1, sizeof(head));
    tot = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 1) {
                for (int k = 0; k < 4; k++) {
                    int ni = i + dx[k], nj = j + dy[k];
                    if (ni >= 1 && ni <= n && nj >= 1 && nj <= m && board[ni][nj] == 1) {
                        addEdge((i - 1) * m + j, (ni - 1) * m + nj, 1);
                        addEdge((ni - 1) * m + nj, (i - 1) * m + j, 1);
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n * m; i++) {
        bfs(i);
    }

    while (q--) {
        scanf("%d%d%d%d%d%d", &ex, &ey, &sx, &sy, &tx, &ty);
        int start = (ex - 1) * m + ey;
        int target = (tx - 1) * m + ty;
        int min_time = dist[start][sx * m + sy];

        if (min_time == 0) {
            printf("-1\n");
            continue;
        }

        int result = min_time + dist[sx * m + sy][target];
        printf("%d\n", result);
    }

    return 0;
}