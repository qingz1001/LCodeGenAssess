#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort的比较
int cmp(const void *a, const void *b) {
    double *x = (double *)a;
    double *y = (double *)b;
    return (*x - *y > 0) ? 1 : -1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    double *v = (double *)malloc(n * sizeof(double)); // 美味度
    double *c = (double *)malloc(n * sizeof(double)); // 消耗时间

    // 读取美味度
    for (int i = 0; i < n; i++) {
        scanf("%lf", &v[i]);
    }

    // 读取消耗时间
    for (int i = 0; i < n; i++) {
        scanf("%lf", &c[i]);
    }

    // 计算美味度与消耗时间的比值
    double *ratio = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        ratio[i] = v[i] / c[i];
    }

    // 按比值从大到小排序
    qsort(ratio, n, sizeof(double), cmp);

    // 初始化结果
    double max_ratio = 0.0;
    double sum_v = 0.0, sum_c = 0.0;

    // 选择前m个比值最大的调料
    for (int i = 0; i < m; i++) {
        sum_v += v[i];
        sum_c += c[i];
        max_ratio = (sum_v / sum_c > max_ratio) ? sum_v / sum_c : max_ratio;
    }

    // 输出结果，保留三位小数
    printf("%.3lf\n", max_ratio);

    // 释放内存
    free(v);
    free(c);
    free(ratio);

    return 0;
}