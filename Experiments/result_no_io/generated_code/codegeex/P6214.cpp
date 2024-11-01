#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 80000
#define MAX_M 80000
#define MAX_Q 300000

typedef struct {
    double x, y, t;
} Point;

typedef struct {
    Point p0, p1;
} Segment;

typedef struct {
    double c, f;
} Query;

int cmp(const void *a, const void *b) {
    Segment *s1 = (Segment *)a;
    Segment *s2 = (Segment *)b;
    double d1 = sqrt((s1->p1.x - s1->p0.x) * (s1->p1.x - s1->p0.x) + (s1->p1.y - s1->p0.y) * (s1->p1.y - s1->p0.y));
    double d2 = sqrt((s2->p1.x - s2->p0.x) * (s2->p1.x - s2->p0.x) + (s2->p1.y - s2->p0.y) * (s2->p1.y - s2->p0.y));
    if (d1 != d2) {
        return d1 - d2 > 0 ? 1 : -1;
    } else {
        return s1->p0.t - s2->p0.t > 0 ? 1 : -1;
    }
}

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);

    Segment a[MAX_N], b[MAX_M];
    Query queries[MAX_Q];

    // 读取初始坐标
    double Ax0, Ay0, Bx0, By0;
    scanf("%lf %lf %lf %lf", &Ax0, &Ay0, &Bx0, &By0);

    // 读取小 A 的移动信息
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &a[i].p1.x, &a[i].p1.y, &a[i].p1.t);
        a[i].p0.x = Ax0;
        a[i].p0.y = Ay0;
        a[i].p0.t = 0;
        Ax0 = a[i].p1.x;
        Ay0 = a[i].p1.y;
    }

    // 读取小 Y 的移动信息
    for (int i = 0; i < m; i++) {
        scanf("%lf %lf %lf", &b[i].p1.x, &b[i].p1.y, &b[i].p1.t);
        b[i].p0.x = Bx0;
        b[i].p0.y = By0;
        b[i].p0.t = 0;
        Bx0 = b[i].p1.x;
        By0 = b[i].p1.y;
    }

    // 读取查询信息
    for (int i = 0; i < q; i++) {
        scanf("%lf %lf", &queries[i].c, &queries[i].f);
    }

    // 对小 A 和小 Y 的移动段进行排序
    qsort(a, n, sizeof(Segment), cmp);
    qsort(b, m, sizeof(Segment), cmp);

    // 处理每个查询
    for (int i = 0; i < q; i++) {
        double c = queries[i].c;
        int f = queries[i].f;
        int count = 0;
        double last_time = -1;

        for (int j = 0; j < n && j < m; j++) {
            double dx = a[j].p1.x - b[j].p1.x;
            double dy = a[j].p1.y - b[j].p1.y;
            double distance = sqrt(dx * dx + dy * dy);

            if (distance == c) {
                count++;
                if (count == f) {
                    last_time = a[j].p1.t;
                    break;
                }
            }
        }

        if (last_time == -1) {
            printf("-4.66\n");
        } else {
            printf("%.8lf\n", last_time);
        }
    }

    return 0;
}