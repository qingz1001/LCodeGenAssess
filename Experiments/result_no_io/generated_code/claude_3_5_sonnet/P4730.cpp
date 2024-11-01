#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int n, m, k, d_min, d_max;
int dist[MAX_N][MAX_N];
bool vis[MAX_N];

void add_edge(int u, int v) {
    edges[cnt].to = v;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

int manhattan_dist(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void bfs(int start, int* d) {
    int queue[MAX_N], front = 0, rear = 0;
    memset(vis, 0, sizeof(vis));
    
    queue[rear++] = start;
    vis[start] = true;
    d[start] = 0;
    
    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            if (!vis[v]) {
                vis[v] = true;
                d[v] = d[u] + 1;
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%d%d", &d_min, &d_max);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &points[i].x, &points[i].y);
    }
    
    scanf("%d", &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d%d", &skills[i].v, &skills[i].u);
    }
    
    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; i++) {
        int a, b, type;
        scanf("%d%d%d", &a, &b, &type);
        add_edge(a, b);
        add_edge(b, a);
    }
    
    for (int i = 1; i <= n; i++) {
        bfs(i, dist[i]);
    }
    
    for (int i = 1; i <= k; i++) {
        int min_time = INF;
        for (int j = 1; j <= k; j++) {
            if (i == j) continue;
            int time_left = dist[skills[i].v][skills[j].v];
            int time_right = dist[skills[i].u][skills[j].u];
            int max_time = (time_left > time_right) ? time_left : time_right;
            if (max_time < min_time) min_time = max_time;
        }
        printf("%d\n", min_time == INF ? -1 : min_time);
    }
    
    return 0;
}