#include <stdio.h>
#include <stdlib.h>

// 定义木棍结构体
typedef struct {
    int length;
    int width;
} Stick;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    Stick *stickA = (Stick *)a;
    Stick *stickB = (Stick *)b;
    if (stickA->length == stickB->length) {
        return stickA->width - stickB->width;
    }
    return stickA->length - stickB->length;
}

int main() {
    int n;
    scanf("%d", &n);
    Stick sticks[n];

    // 读取木棍长度和宽度
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &sticks[i].length, &sticks[i].width);
    }

    // 对木棍进行排序
    qsort(sticks, n, sizeof(Stick), compare);

    // 计算最短准备时间
    int prepareTime = 1;
    for (int i = 1; i < n; i++) {
        if (sticks[i].length < sticks[i-1].length || sticks[i].width < sticks[i-1].width) {
            prepareTime++;
        }
    }

    // 输出结果
    printf("%d\n", prepareTime);

    return 0;
}