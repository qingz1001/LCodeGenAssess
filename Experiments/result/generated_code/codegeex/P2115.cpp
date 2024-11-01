#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[100001], s[100001], b[100001], c[100001], d[100001], e[100001];
    double minn = 1000000.0;

    // 读取输入并计算前缀和
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
    }

    // 计算b数组
    for (int i = 1; i <= n; i++) {
        b[i] = s[i] - a[i] / 2;
    }

    // 计算c数组
    for (int i = 1; i <= n; i++) {
        c[i] = b[i] - b[1] + b[i - 1];
    }

    // 计算d数组
    for (int i = 1; i <= n; i++) {
        d[i] = s[n] - s[i] - a[i] / 2;
    }

    // 计算e数组
    for (int i = 1; i <= n; i++) {
        e[i] = d[i] - d[1] + d[i - 1];
    }

    // 找到最小的平均产奶量
    for (int i = 2; i < n; i++) {
        if ((c[i] + e[i]) / (double)(n - i) < minn) {
            minn = (c[i] + e[i]) / (double)(n - i);
        }
    }

    // 输出结果，保留三位小数
    printf("%.3lf\n", minn);

    return 0;
}