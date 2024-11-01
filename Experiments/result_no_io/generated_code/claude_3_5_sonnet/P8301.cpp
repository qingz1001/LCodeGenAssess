#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int main() {
    int n;
    int a[MAX_N], b[MAX_N];
    int count_a = 0, count_b = 0;

    // 读取输入
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (a[i] == 1) count_a++;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        if (b[i] == 1) count_b++;
    }

    // 计算需要取反的最少次数
    int min_flips = abs(count_a - count_b);

    // 输出结果
    printf("%d\n", min_flips);

    return 0;
}