#include <stdio.h>
#include <math.h>

int main() {
    int n, i, j, k, count, ans = 0, ways = 1;
    scanf("%d", &n);

    // 从1开始枚举，直到找到一个满足条件的数
    for (i = 1; ; i++) {
        int sum = 0;
        int a[1001] = {0}; // 用于存储已经选取的数
        a[0] = i; // 第一个数是i

        // 动态规划求解
        for (j = 1; j <= n; j++) {
            for (k = 0; k < j; k++) {
                if (a[k] <= j && !a[j - a[k]]) {
                    a[j] = a[k] + a[j - a[k]];
                    break;
                }
            }
            if (a[j] == 0) {
                sum = j + 1;
                break;
            }
        }

        // 如果找到了一个满足条件的数
        if (sum == n + 1) {
            ans = i;
            break;
        }
    }

    // 统计有多少种不同的方案
    for (i = ans + 1; i <= n; i++) {
        int a[1001] = {0};
        a[0] = i;
        for (j = 1; j <= n; j++) {
            for (k = 0; k < j; k++) {
                if (a[k] <= j && !a[j - a[k]]) {
                    a[j] = a[k] + a[j - a[k]];
                    break;
                }
            }
            if (a[j] == 0) {
                break;
            }
        }
        if (j == n + 1) {
            ways++;
        }
    }

    printf("%d %d\n", ans, ways);
    return 0;
}