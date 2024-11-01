#include <stdio.h>
#include <stdlib.h>

int main() {
    int w, n, i, j, count = 0;
    int *prices;

    // 读取输入
    scanf("%d", &w);
    scanf("%d", &n);
    prices = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    // 对纪念品价格进行排序
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (prices[j] > prices[j + 1]) {
                int temp = prices[j];
                prices[j] = prices[j + 1];
                prices[j + 1] = temp;
            }
        }
    }

    // 使用双指针法进行分组
    i = 0;
    j = n - 1;
    while (i <= j) {
        if (prices[i] + prices[j] <= w) {
            i++;
        }
        j--;
        count++;
    }

    // 输出最少的分组数目
    printf("%d\n", count);

    // 释放内存
    free(prices);

    return 0;
}