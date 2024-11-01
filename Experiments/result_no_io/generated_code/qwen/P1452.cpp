#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 50005

typedef struct {
    int x, y;
} Point;

Point p[MAXN];
int n;

// 比较函数，用于排序
int compare(const void *a, const void *b) {
    return ((Point *)a)->x - ((Point *)b)->x;
}

// 计算两点之间的距离平方
int dist2(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

// 计算向量叉积
int cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &p[i].x, &p[i].y);
    }

    // 按照 x 坐标排序
    qsort(p, n, sizeof(Point), compare);

    // 找到最左边和最右边的点
    Point leftmost = p[0], rightmost = p[n-1];

    // 初始化凸包直径为最左边和最右边的点的距离平方
    int max_dist2 = dist2(leftmost, rightmost);

    // 使用旋转卡壳算法
    int i = 0, j = n - 1;
    while (i != j) {
        int next_i = (i + 1) % n;
        int next_j = (j - 1 + n) % n;

        if (cross(leftmost, p[next_i], p[j]) > cross(leftmost, p[next_j], p[j])) {
            i = next_i;
        } else {
            j = next_j;
        }

        max_dist2 = fmax(max_dist2, dist2(leftmost, p[i]));
        max_dist2 = fmax(max_dist2, dist2(rightmost, p[j]));
    }

    printf("%d\n", max_dist2);

    return 0;
}