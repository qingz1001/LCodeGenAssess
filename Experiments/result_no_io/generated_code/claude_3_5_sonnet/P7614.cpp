#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Number;

int compare(const void *a, const void *b) {
    return ((Number *)b)->value - ((Number *)a)->value;
}

int main() {
    Number numbers[8];
    int i, sum = 0;

    // 读取输入
    for (i = 0; i < 8; i++) {
        scanf("%d", &numbers[i].value);
        numbers[i].index = i + 1;
    }

    // 按值从大到小排序
    qsort(numbers, 8, sizeof(Number), compare);

    // 计算前5个数的和
    for (i = 0; i < 5; i++) {
        sum += numbers[i].value;
    }

    // 输出和
    printf("%d\n", sum);

    // 按索引从小到大排序前5个数
    for (i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (numbers[i].index > numbers[j].index) {
                Number temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }

    // 输出索引
    for (i = 0; i < 5; i++) {
        printf("%d ", numbers[i].index);
    }
    printf("\n");

    return 0;
}