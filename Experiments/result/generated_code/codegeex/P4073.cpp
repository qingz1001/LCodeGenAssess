#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 100005
#define MAXM 100005

typedef struct Point {
    double x, y;
} Point;

typedef struct Edge {
    int u, v, h;
} Edge;

Point points[MAXN];
Edge edges[MAXM];
int n, m, q;

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    if (edgeA->h != edgeB->h) {
        return edgeA->h - edgeB->h;
    } else {
        return (edgeA->u + edgeA->v) - (edgeB->u + edgeB->v);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].h);
    }
    qsort(edges, m, sizeof(Edge), compare);

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        double Ax, Ay, Bx, By;
        scanf("%lf %lf %lf %lf", &Ax, &Ay, &Bx, &By);
        // 解答每个询问的逻辑
        // 注意：这部分逻辑需要根据题意自行实现
        printf("0\n"); // 这里只是一个示例，实际应该根据题意进行计算
    }

    return 0;
}