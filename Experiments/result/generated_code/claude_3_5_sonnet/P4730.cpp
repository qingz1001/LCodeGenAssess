#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 1005
#define MAX_M 4005
#define MAX_K 10005
#define INF 0x3f3f3f3f

typedef struct {
    int x, y;
} Point;

typedef struct {
    int v, u;
} Skill;

typedef struct {
    int to, next;
} Edge;

Point points[MAX_N];
Skill skills[MAX_K];
Edge edges[MAX_M * 2];
int head[MAX_N], cnt;
int dist[MAX_N][MAX_N];
int n, m, k, d_min, d_max;

void add_edge(int u, int v) {
    edges[cnt].to = v;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

int manhattan_dist(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%d %d", &d_min, &d_max);

    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    scanf("%d", &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d %d", &skills[i].v, &skills[i].u);
    }

    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; i++) {
        int a, b, type;
        scanf("%d %d %d", &a, &b, &type);
        if (type == 0) {
            add_edge(a, b);
            add_edge(b, a);
        } else {
            add_edge(a + n, b + n);
            add_edge(b + n, a + n);
        }
    }

    memset(dist, 0x3f, sizeof(dist));
    for (int i = 1; i <= n * 2; i++) {
        dist[i][i] = 0;
        for (int e = head[i]; ~e; e = edges[e].next) {
            int j = edges[e].to;
            dist[i][j] = 1;
        }
    }

    floyd();

    for (int i = 1; i <= k; i++) {
        int min_time = INF;
        for (int j = 1; j <= k; j++) {
            if (i == j) continue;
            int time_left = dist[skills[i].v][skills[j].v];
            int time_right = dist[skills[i].u + n][skills[j].u + n];
            int max_time = (time_left > time_right ? time_left : time_right);
            if (max_time < min_time) min_time = max_time;
        }
        printf("%d\n", min_time == INF ? -1 : min_time);
    }

    return 0;
}