#include <stdio.h>
#include <stdlib.h>

// 定义最大点数
#define MAX_POINTS 5000

// 定义点结构体
typedef struct {
    double x;
    double y;
} Point;

// 计算两点之间的斜率
double calculateSlope(Point p1, Point p2) {
    return (p2.y - p1.y) / (p2.x - p1.x);
}

int main() {
    int n;
    scanf("%d", &n);

    Point points[MAX_POINTS];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    // 计算每一段的斜率
    double slopes[n-1];
    for (int i = 0; i < n-1; i++) {
        slopes[i] = calculateSlope(points[i], points[i+1]);
    }

    // 计算最大斜率
    double maxSlope = slopes[0];
    for (int i = 1; i < n-1; i++) {
        if (slopes[i] > maxSlope) {
            maxSlope = slopes[i];
        }
    }

    // 输出最小的y坐标，即最大斜率的两倍
    printf("%.2lf\n", maxSlope * 2);

    return 0;
}