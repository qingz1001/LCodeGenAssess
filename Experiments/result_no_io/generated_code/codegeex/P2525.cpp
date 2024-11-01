#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int a[N];

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    // 找到从右往左第一个升序的数
    int i;
    for (i = N - 2; i >= 0; i--) {
        if (a[i] > a[i + 1]) {
            break;
        }
    }

    // 如果找不到，说明当前排列已经是第一个
    if (i == -1) {
        printf("ERROR");
        return 0;
    }

    // 找到i右侧比a[i]小的最大值
    int max = i + 1;
    for (int j = i + 2; j < N; j++) {
        if (a[j] < a[i] && a[j] > a[max]) {
            max = j;
        }
    }

    // 交换a[i]和a[max]
    int temp = a[i];
    a[i] = a[max];
    a[max] = temp;

    // 将i+1到末尾部分进行降序排列
    for (int j = i + 1; j < N - 1; j++) {
        for (int k = j + 1; k < N; k++) {
            if (a[j] < a[k]) {
                temp = a[j];
                a[j] = a[k];
                a[k] = temp;
            }
        }
    }

    // 输出结果
    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}