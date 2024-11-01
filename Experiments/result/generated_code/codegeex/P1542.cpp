#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int main() {
    int n;
    scanf("%d", &n);

    int xi[MAXN], yi[MAXN], si[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &xi[i], &yi[i], &si[i]);
    }

    double left = 0.0, right = 1e10, mid;
    while (right - left > 1e-5) {
        mid = (left + right) / 2.0;
        double current_time = 0.0;

        for (int i = 0; i < n; i++) {
            // 计算到达当前地点的时间
            current_time += si[i] / mid;

            // 判断是否需要停留
            if (current_time < xi[i]) {
                // 如果到达时间早于可以签收的时间段，需要停留
                current_time = xi[i];
            } else if (current_time > yi[i]) {
                // 如果到达时间晚于可以签收的时间段，说明当前速度不合理
                right = mid;
                break;
            }
        }

        // 如果当前速度合理且可以到达最后一个地点
        if (current_time <= yi[n-1]) {
            right = mid;
        } else {
            left = mid;
        }
    }

    // 输出结果，保留两位小数
    printf("%.2f\n", right);
    return 0;
}