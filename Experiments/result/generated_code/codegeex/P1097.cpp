#include <stdio.h>
#include <stdlib.h>

// 定义一个结构体来存储数字和出现次数
typedef struct {
    long long num;
    int count;
} Number;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    Number *num1 = (Number *)a;
    Number *num2 = (Number *)b;
    return (num1->num - num2->num);
}

int main() {
    int n;
    scanf("%d", &n);

    Number *numbers = (Number *)malloc(n * sizeof(Number));
    if (numbers == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // 读取输入
    for (int i = 0; i < n; i++) {
        scanf("%lld", &numbers[i].num);
        numbers[i].count = 1;
    }

    // 使用qsort对数组进行排序
    qsort(numbers, n, sizeof(Number), compare);

    // 统计每个数字出现的次数
    int i = 0;
    while (i < n) {
        int j = i + 1;
        while (j < n && numbers[j].num == numbers[i].num) {
            numbers[i].count++;
            j++;
        }
        i = j;
    }

    // 输出结果
    for (int i = 0; i < n; i++) {
        if (numbers[i].count > 0) {
            printf("%lld %d\n", numbers[i].num, numbers[i].count);
        }
    }

    // 释放内存
    free(numbers);

    return 0;
}