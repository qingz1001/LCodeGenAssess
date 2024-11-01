#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1005
#define INF INT_MAX

typedef struct {
    int x, y;
} Point;

int n, m, k, d_min, d_max;
Point points[MAXN];
int moves[MAXN][MAXN];
int adj[MAXN][MAXN];

void init() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            moves[i][j] = adj[i][j] = 0;
        }
    }
}

int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void read_input() {
    scanf("%d %d", &n, &m);
    scanf("%d %d", &d_min, &d_max);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; ++i) {
        int v, u;
        scanf("%d %d", &v, &u);
        adj[v][u] = adj[u][v] = 1;
    }
    for (int i = 0; i < m; ++i) {
        int a, b, type;
        scanf("%d %d %d", &a, &b, &type);
        if (type == 0) {
            moves[a][b] = moves[b][a] = 1;
        } else {
            moves[n + a][n + b] = moves[n + b][n + a] = 1;
        }
    }
}

int bfs(int start, int end) {
    int dist[MAXN];
    for (int i = 0; i <= n * 2; ++i) {
        dist[i] = INF;
    }
    dist[start] = 0;
    for (int i = 0; i <= n * 2; ++i) {
        for (int j = 0; j <= n * 2; ++j) {
            if (moves[i][j]) {
                int new_dist = dist[i] + 1;
                if (new_dist < dist[j]) {
                    dist[j] = new_dist;
                }
            }
        }
    }
    return dist[end];
}

int main() {
    init();
    read_input();
    for (int i = 1; i <= k; ++i) {
        int v, u;
        scanf("%d %d", &v, &u);
        int min_time = INF;
        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= n; ++y) {
                if (manhattan(points[x].x, points[x].y, points[v].x, points[v].y) >= d_min &&
                    manhattan(points[y].x, points[y].y, points[u].x, points[u].y) >= d_min) {
                    int time_to_v = bfs(n + x, v);
                    int time_to_u = bfs(n + y, u);
                    if (time_to_v != INF && time_to_u != INF) {
                        min_time = fmin(min_time, time_to_v + time_to_u);
                    }
                }
            }
        }
        printf("%d\n", min_time == INF ? -1 : min_time);
    }
    return 0;
}