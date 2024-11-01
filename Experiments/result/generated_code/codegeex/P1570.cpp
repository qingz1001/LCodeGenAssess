#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int v[n], c[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
    }

    // 排序，根据美味度/消耗时间比降序排列
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((double)v[j] / c[j] < (double)v[j + 1] / c[j + 1]) {
                int temp_v = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp_v;

                int temp_c = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp_c;
            }
        }
    }

    // 计算前m种调料的美味度总和和消耗时间总和
    int sum_v = 0, sum_c = 0;
    for (int i = 0; i < m; i++) {
        sum_v += v[i];
        sum_c += c[i];
    }

    // 计算最大单位时间美味度
    double max_beauty = (double)sum_v / sum_c;
    printf("%.3lf\n", max_beauty);

    return 0;
}