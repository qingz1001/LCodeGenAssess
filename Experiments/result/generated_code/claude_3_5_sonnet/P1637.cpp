#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30000
#define MAX_A 100000

long long count_thair(int n, int *a) {
    long long count = 0;
    int less[MAX_N] = {0};
    int greater[MAX_N] = {0};
    int freq[MAX_A + 1] = {0};

    // 计算每个元素左边比它小的元素个数
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < a[i]; j++) {
            less[i] += freq[j];
        }
        freq[a[i]]++;
    }

    // 重置频率数组
    for (int i = 1; i <= MAX_A; i++) {
        freq[i] = 0;
    }

    // 计算每个元素右边比它大的元素个数
    for (int i = n - 1; i >= 0; i--) {
        for (int j = a[i] + 1; j <= MAX_A; j++) {
            greater[i] += freq[j];
        }
        freq[a[i]]++;
    }

    // 计算thair的总数
    for (int i = 1; i < n - 1; i++) {
        count += (long long)less[i] * greater[i];
    }

    return count;
}

int main() {
    int n;
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    long long result = count_thair(n, a);
    printf("%lld\n", result);

    free(a);
    return 0;
}