#include <stdio.h>

#define MAXN 100001

int a[MAXN];
int sum[MAXN];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // 计算前缀和
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }

    double min_avg = 10000.0; // 初始化为一个很大的值

    // 枚举断开的区间 [2, n-1]
    for (int i = 2; i < n; i++) {
        double left_sum = sum[i - 1];
        double right_sum = sum[n] - sum[i];
        int count_left = i - 1;
        int count_right = n - i;

        // 计算剩余机器的最小平均产奶量
        double avg = (left_sum + right_sum) / (count_left + count_right);
        if (avg < min_avg) {
            min_avg = avg;
        }
    }

    // 输出结果，保留三位小数
    printf("%.3lf\n", min_avg);

    return 0;
}