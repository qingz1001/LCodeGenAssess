#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int* scores = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &scores[i]);
    }

    // 将分数数组按升序排序
    qsort(scores, n, sizeof(int), cmpfunc);

    // 初始最高分和最低分的差值
    long long diff = (long long)scores[n-1] - scores[0];

    // 如果可以进行操作，则增加差值
    if (m > 0) {
        diff += m;
    }

    // 输出最终得分乘以(n-2)的结果
    printf("%lld\n", diff * (n - 2));

    free(scores);
    return 0;
}

// 比较函数，用于qsort
int cmpfunc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}