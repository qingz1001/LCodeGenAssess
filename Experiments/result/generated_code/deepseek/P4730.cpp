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
int adj[MAXN + 1][MAXN + 1];
int dist[MAXN + 1][MAXN + 1];
int min_dist[MAXK + 1];

int abs(int x) {
    return x < 0 ? -x : x;
}

int manhattan_dist(int i, int j) {
    return abs(points[i].x - points[j].x) + abs(points[i].y - points[j].y);
}

void floyd_warshall(int n) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int d_min, d_max;
    scanf("%d %d", &d_min, &d_max);

    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    int k;
    scanf("%d", &k);

    for (int i = 1; i <= k; i++) {
        scanf("%d %d", &moves[i].v, &moves[i].u);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = INT_MAX;
        }
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int a, b, type;
        scanf("%d %d %d", &a, &b, &type);
        if (type == 0) {
            adj[a][b] = 1;
            adj[b][a] = 1;
        } else {
            adj[a][b] = 2;
            adj[b][a] = 2;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (adj[i][j] == 1) {
                dist[i][j] = 1;
            } else if (adj[i][j] == 2) {
                dist[i][j] = 1;
            }
        }
    }

    floyd_warshall(n);

    for (int i = 1; i <= k; i++) {
        min_dist[i] = INT_MAX;
        for (int j = 1; j <= k; j++) {
            if (i != j) {
                int left_dist = dist[moves[i].v][moves[j].v];
                int right_dist = dist[moves[i].u][moves[j].u];
                if (left_dist != INT_MAX && right_dist != INT_MAX) {
                    int total_dist = left_dist + right_dist;
                    if (total_dist < min_dist[i]) {
                        min_dist[i] = total_dist;
                    }
                }
            }
        }
        if (min_dist[i] == INT_MAX) {
            min_dist[i] = -1;
        }
    }

    for (int i = 1; i <= k; i++) {
        printf("%d\n", min_dist[i]);
    }

    return 0;
}