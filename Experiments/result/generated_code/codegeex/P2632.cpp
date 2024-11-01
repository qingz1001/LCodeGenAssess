#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 计算两点之间的欧几里得距离
double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// 比较函数，用于qsort
int compare(const void *a, const void *b) {
    return (*(double*)a - *(double*)b) < 0 ? -1 : 1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int AX, AY, BX, BY, CX, CY, DX, DY;
    scanf("%d %d %d %d %d %d %d %d", &AX, &AY, &BX, &BY, &CX, &CY, &DX, &DY);

    double *points1 = (double*)malloc(n * sizeof(double));
    double *points2 = (double*)malloc(m * sizeof(double));

    for (int i = 0; i < n; i++) {
        scanf("%lf", &points1[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%lf", &points2[i]);
    }

    // 对点进行排序
    qsort(points1, n, sizeof(double), compare);
    qsort(points2, m, sizeof(double), compare);

    double totalDistance = 0.0;

    // 计算最小生成树
    for (int i = 0; i < n; i++) {
        double x1 = AX * points1[i] + BX * (1 - points1[i]);
        double y1 = AY * points1[i] + BY * (1 - points1[i]);
        for (int j = 0; j < m; j++) {
            double x2 = CX * points2[j] + DX * (1 - points2[j]);
            double y2 = CY * points2[j] + DY * (1 - points2[j]);
            totalDistance += distance(x1, y1, x2, y2);
        }
    }

    // 输出结果，四舍五入至三位小数
    printf("%.3lf\n", totalDistance);

    free(points1);
    free(points2);

    return 0;
}