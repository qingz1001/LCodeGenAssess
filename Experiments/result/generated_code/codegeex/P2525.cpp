#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int a[N];

    // 读取输入的排列
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    // 从后向前查找第一个相邻升序的元素对
    int i;
    for (i = N - 2; i >= 0; i--) {
        if (a[i] > a[i + 1]) {
            break;
        }
    }

    // 如果没有找到这样的元素对，说明当前排列已经是第一个，输出ERROR
    if (i == -1) {
        printf("ERROR\n");
        return 0;
    }

    // 找到第一个比a[i]小的元素a[j]
    int j;
    for (j = N - 1; j > i; j--) {
        if (a[j] < a[i]) {
            break;
        }
    }

    // 交换a[i]和a[j]
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;

    // 反转i后面的元素
    for (int l = i + 1, r = N - 1; l < r; l++, r--) {
        temp = a[l];
        a[l] = a[r];
        a[r] = temp;
    }

    // 输出结果
    for (int k = 0; k < N; k++) {
        printf("%d ", a[k]);
    }
    printf("\n");

    return 0;
}