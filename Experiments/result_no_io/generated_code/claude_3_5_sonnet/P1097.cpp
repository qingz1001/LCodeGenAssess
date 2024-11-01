#include <stdio.h>
#include <stdlib.h>

#define MAX_UNIQUE 10000

typedef struct {
    int number;
    int count;
} NumberCount;

int compare(const void *a, const void *b) {
    return ((NumberCount*)a)->number - ((NumberCount*)b)->number;
}

int main() {
    int n, i, j, num, uniqueCount = 0;
    NumberCount counts[MAX_UNIQUE];

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &num);

        // 查找数字是否已存在
        for (j = 0; j < uniqueCount; j++) {
            if (counts[j].number == num) {
                counts[j].count++;
                break;
            }
        }

        // 如果是新数字，添加到数组中
        if (j == uniqueCount) {
            counts[uniqueCount].number = num;
            counts[uniqueCount].count = 1;
            uniqueCount++;
        }
    }

    // 按数字大小排序
    qsort(counts, uniqueCount, sizeof(NumberCount), compare);

    // 输出结果
    for (i = 0; i < uniqueCount; i++) {
        printf("%d %d\n", counts[i].number, counts[i].count);
    }

    return 0;
}