#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000
#define MAXM 4000
#define MAXK 10000

typedef struct {
    int x, y;
} Point;

typedef struct {
    int v, u;
} Move;

Point points[MAXN + 1];
Move moves[MAXM + 1];
int adj_left[MAXN + 1][MAXN + 1];
int adj_right[MAXN + 1][MAXN + 1];
int dist[MAXN + 1][MAXN + 1];
int min_time[MAXK + 1];

int abs(int x) {
    return x < 0 ? -x : x;
}

int manhattan_dist(int i, int j) {
    return abs(points[i].x - points[j].x) + abs(points[i].y - points[j].y);
}

void bfs(int start, int n, int adj[MAXN + 1][MAXN + 1], int dist[MAXN + 1]) {
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;
    queue[rear++] = start;
    while (front < rear) {
        int u = queue[front++];
        for (int v = 1; v <= n; v++) {
            if (adj[u][v] && dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    int n, m, d_min, d_max, k;
    scanf("%d %d", &n, &m);
    scanf("%d %d", &d_min, &d_max);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d %d", &moves[i].v, &moves[i].u);
    }
    for (int i = 1; i <= m; i++) {
        int a, b, type;
        scanf("%d %d %d", &a, &b, &type);
        if (type == 0) {
            adj_left[a][b] = adj_left[b][a] = 1;
        } else {
            adj_right[a][b] = adj_right[b][a] = 1;
        }
    }

    for (int i = 1; i <= k; i++) {
        min_time[i] = INT_MAX;
    }

    for (int i = 1; i <= k; i++) {
        int v = moves[i].v, u = moves[i].u;
        bfs(v, n, adj_left, dist[v]);
        bfs(u, n, adj_right, dist[u]);
        for (int j = 1; j <= k; j++) {
            if (i == j) continue;
            int v2 = moves[j].v, u2 = moves[j].u;
            if (dist[v][v2] != INT_MAX && dist[u][u2] != INT_MAX) {
                int time = dist[v][v2] + dist[u][u2];
                if (manhattan_dist(v2, u2) >= d_min && manhattan_dist(v2, u2) <= d_max) {
                    min_time[i] = min_time[i] < time ? min_time[i] : time;
                }
            }
        }
    }

    for (int i = 1; i <= k; i++) {
        if (min_time[i] == INT_MAX) {
            printf("-1\n");
        } else {
            printf("%d\n", min_time[i]);
        }
    }

    return 0;
}