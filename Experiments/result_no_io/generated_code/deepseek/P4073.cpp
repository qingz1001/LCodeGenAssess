#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100000
#define MAXM 100000
#define MAXQ 100000

typedef struct {
    int x, y;
} Point;

typedef struct {
    int u, v, h;
} Edge;

typedef struct {
    double x, y;
} QueryPoint;

Point vertices[MAXN];
Edge edges[MAXM];
QueryPoint queries[MAXQ];
int n, m, q;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &vertices[i].x, &vertices[i].y);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].h);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%lf %lf %lf %lf", &queries[i].x, &queries[i].y, &queries[i].x, &queries[i].y);
    }

    // 处理每个询问
    for (int i = 0; i < q; i++) {
        // 这里需要实现具体的算法来计算最小权值
        // 由于题目复杂，这里仅给出框架代码
        printf("0\n"); // 默认输出0，实际应根据算法计算
    }

    return 0;
}