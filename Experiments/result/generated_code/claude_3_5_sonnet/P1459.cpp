#include <stdio.h>

#define MAX_N 1000

int main() {
    int n, i;
    int sequence[MAX_N];
    int count[4] = {0};  // 用于统计1,2,3的数量，index 0不使用
    int position[4] = {0};  // 用于记录1,2,3应该在的位置
    int swaps = 0;

    // 读取输入
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &sequence[i]);
        count[sequence[i]]++;
    }

    // 计算每个数字应该在的位置
    position[1] = 0;
    position[2] = count[1];
    position[3] = count[1] + count[2];

    // 计算最少交换次数
    for (i = 0; i < n; i++) {
        while (sequence[i] != i / count[sequence[i]] + 1) {
            int correct_pos = position[sequence[i]];
            int temp = sequence[correct_pos];
            sequence[correct_pos] = sequence[i];
            sequence[i] = temp;
            position[sequence[correct_pos]]++;
            swaps++;
        }
    }

    // 输出结果
    printf("%d\n", swaps);

    return 0;
}