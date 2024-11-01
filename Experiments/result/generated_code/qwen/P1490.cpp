#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    // 计算最少需要多少个数
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if ((i * (i + 1)) / 2 >= n) {
            count = i;
            break;
        }
    }

    // 计算用最少个数的组成方案个数
    int ways = 0;
    int sum = 0;
    for (int i = 1; i <= count; i++) {
        sum += i;
        if (sum == n) {
            ways++;
        } else if (sum > n) {
            break;
        }
    }

    printf("%d %d\n", count, ways);

    return 0;
}