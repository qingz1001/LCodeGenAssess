#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int times[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &times[i]);
    }

    // 按照接水时间从小到大排序
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (times[i] > times[j]) {
                int temp = times[i];
                times[i] = times[j];
                times[j] = temp;
            }
        }
    }

    // 输出排序后的顺序
    for (int i = 0; i < n; i++) {
        printf("%d ", times[i]);
    }
    printf("\n");

    // 计算平均等待时间
    double totalWaitTime = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            totalWaitTime += times[j];
        }
    }
    double averageWaitTime = totalWaitTime / n;

    // 输出平均等待时间
    printf("%.2lf\n", averageWaitTime);

    return 0;
}