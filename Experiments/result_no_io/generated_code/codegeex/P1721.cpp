#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);

    int *heights = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    // 对高度进行排序
    qsort(heights, n, sizeof(int), (int (*)(const void *, const void *))strcmp);

    // 找到1号城市的索引
    int index_of_one = -1;
    for (int i = 0; i < n; i++) {
        if (heights[i] == 1) {
            index_of_one = i;
            break;
        }
    }

    // 初始化结果
    double max_height = 1.0;

    // 尝试不同的连接方案
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int count = 0;
            double average_height = 0.0;

            // 计算当前连接方案的平均高度
            for (int l = i; l <= j; l++) {
                average_height += heights[l];
                count++;
            }
            average_height /= count;

            // 如果当前平均高度大于当前最大高度，更新最大高度
            if (average_height > max_height) {
                max_height = average_height;
            }
        }
    }

    // 输出结果
    printf("%.2lf\n", max_height);

    free(heights);
    return 0;
}