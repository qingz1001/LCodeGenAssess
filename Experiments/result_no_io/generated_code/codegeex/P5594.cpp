#include <stdio.h>

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    int a[1001][1001] = {0};

    // 读取输入数据
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int day;
            scanf("%d", &day);
            a[day][j]++;
        }
    }

    // 计算每天需要准备的模拟赛场数
    for (int i = 1; i <= k; i++) {
        int count = 0;
        for (int j = 0; j < m; j++) {
            count += a[i][j];
        }
        printf("%d ", count);
    }

    return 0;
}