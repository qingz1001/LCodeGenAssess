#include <stdio.h>
#include <stdlib.h>

#define MAXN 35000

int n;
int a[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // 计算最少需要改变多少个数
    int changes = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] <= a[i - 1]) {
            changes++;
        }
    }

    // 计算在改变的数最少的情况下，每个数改变的绝对值之和的最小值
    int sum = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] <= a[i - 1]) {
            sum += a[i - 1] - a[i];
            a[i] = a[i - 1] + 1;
        }
    }

    printf("%d\n", changes);
    printf("%d\n", sum);

    return 0;
}