#include <stdio.h>

#define MAX_N 1000

int main() {
    int n;
    int sequence[MAX_N];
    int count[4] = {0};  // 用于统计1,2,3的个数，索引0不使用
    int pos[4] = {0};    // 用于记录1,2,3应该在的位置
    int swaps = 0;

    // 读取输入
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &sequence[i]);
        count[sequence[i]]++;
    }

    // 计算每个数字应该在的位置
    pos[1] = 0;
    pos[2] = count[1];
    pos[3] = count[1] + count[2];

    // 计算需要交换的次数
    for (int i = 1; i <= 3; i++) {
        for (int j = pos[i]; j < pos[i] + count[i]; j++) {
            if (sequence[j] != i) {
                int k = j + 1;
                while (k < n && sequence[k] != i) {
                    k++;
                }
                // 交换
                int temp = sequence[j];
                sequence[j] = sequence[k];
                sequence[k] = temp;
                swaps++;
            }
        }
    }

    // 输出结果
    printf("%d\n", swaps);

    return 0;
}