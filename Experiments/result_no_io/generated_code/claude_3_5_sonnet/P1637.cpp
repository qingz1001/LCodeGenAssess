#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30000
#define MAX_A 100000

int main() {
    int n, i, j;
    int a[MAX_N];
    int smaller[MAX_N] = {0};
    int larger[MAX_N] = {0};
    long long count = 0;

    // 读取输入
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // 计算每个元素左侧比它小的元素个数
    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                smaller[i]++;
            }
        }
    }

    // 计算每个元素右侧比它大的元素个数
    for (i = n - 2; i >= 0; i--) {
        for (j = i + 1; j < n; j++) {
            if (a[j] > a[i]) {
                larger[i]++;
            }
        }
    }

    // 计算thair的总数
    for (i = 1; i < n - 1; i++) {
        count += (long long)smaller[i] * larger[i];
    }

    // 输出结果
    printf("%lld\n", count);

    return 0;
}