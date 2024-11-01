#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAXN 1005
#define MAXV 10005

struct Rectangle {
    int x1, y1, x2, y2;
};

struct Node {
    int u, v, w;
};

Rectangle rectangles[MAXN];
Node graph[MAXN * 2];
int head[MAXN * 2], dis[MAXN * 2], vis[MAXN * 2], pre[MAXN * 2], cnt;
double v;

void addEdge(int u, int v, int w) {
    graph[cnt].u = u;
    graph[cnt].v = v;
    graph[cnt].w = w;
    graph[cnt].w += dis[u];
    graph[cnt + 1].u = v;
    graph[cnt + 1].v = u;
    graph[cnt + 1].w = 0;
    head[u] = cnt++;
}

void dijkstra(int start) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[start] = 0;
    int u, v, w;
    while (1) {
        u = -1;
        for (int i = 0; i < cnt; i++) {
            if (!vis[graph[i].u] && (u == -1 || dis[graph[i].u] < dis[u])) {
                u = graph[i].u;
            }
        }
        if (u == -1) break;
        vis[u] = 1;
        for (int i = head[u]; i != -1; i = graph[i].w) {
            v = graph[i].v;
            w = graph[i].w;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pre[v] = i;
            }
        }
    }
}

int main() {
    int n, startX, startY, endX, endY, start, end, w;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &rectangles[i].x1, &rectangles[i].y1, &rectangles[i].x2, &rectangles[i].y2);
    }
    scanf("%d%d%d%d", &startX, &startY, &endX, &endY);
    scanf("%lf", &v);

    memset(head, -1, sizeof(head));
    cnt = 0;

    for (int i = 0; i < n; i++) {
        if (rectangles[i].y1 <= startY && startY <= rectangles[i].y2) {
            addEdge(i, n + i, rectangles[i].x2 - startX);
        }
        if (rectangles[i].y1 <= endY && endY <= rectangles[i].y2) {
            addEdge(n + i, i, endX - rectangles[i].x1);
        }
        for (int j = i + 1; j < n; j++) {
            if (rectangles[i].x2 == rectangles[j].x1 && rectangles[i].y2 >= rectangles[j].y1 && rectangles[j].y2 >= rectangles[i].y1) {
                addEdge(i, j, rectangles[j].x1 - rectangles[i].x2);
                addEdge(j, i, rectangles[j].x1 - rectangles[i].x2);
            }
        }
    }

    start = -1;
    end = -1;
    for (int i = 0; i < n; i++) {
        if (rectangles[i].x1 <= startX && startX <= rectangles[i].x2) {
            start = i;
        }
        if (rectangles[i].x1 <= endX && endX <= rectangles[i].x2) {
            end = i;
        }
    }
    if (start == -1) {
        for (int i = 0; i < n; i++) {
            if (rectangles[i].y1 <= startY && startY <= rectangles[i].y2) {
                start = n + i;
                break;
            }
        }
    }
    if (end == -1) {
        for (int i = 0; i < n; i++) {
            if (rectangles[i].y1 <= endY && endY <= rectangles[i].y2) {
                end = n + i;
                break;
            }
        }
    }

    dijkstra(start);

    if (dis[end] == dis[0]) {
        printf("No solution\n");
    } else {
        printf("%.6lf\n", (double)dis[end] / v);
    }

    return 0;
}