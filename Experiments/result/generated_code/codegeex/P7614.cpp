#include <stdio.h>

int main() {
    int X[8], sum = 0, max[5] = {0}, indices[5] = {0};
    int maxIndex[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    // 读取输入的8个数字
    for (int i = 0; i < 8; i++) {
        scanf("%d", &X[i]);
    }

    // 找出最大的5个数字及其索引
    for (int i = 0; i < 5; i++) {
        int maxVal = 0, maxIdx = 0;
        for (int j = 0; j < 8; j++) {
            if (X[j] > maxVal && maxIndex[j] == 0) {
                maxVal = X[j];
                maxIdx = j;
            }
        }
        max[i] = maxVal;
        indices[i] = maxIdx + 1;
        maxIndex[maxIdx] = 1;
    }

    // 计算最大的5个数字的和
    for (int i = 0; i < 5; i++) {
        sum += max[i];
    }

    // 输出结果
    printf("%d\n", sum);
    for (int i = 0; i < 5; i++) {
        printf("%d ", indices[i]);
    }
    printf("\n");

    return 0;
}