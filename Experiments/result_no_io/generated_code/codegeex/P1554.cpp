#include <stdio.h>

int main() {
    int M, N;
    scanf("%d %d", &M, &N);

    int count[10] = {0}; // 初始化计数数组

    // 统计每个数字在区间 [M, N] 中出现的次数
    for (int i = M; i <= N; i++) {
        int num = i;
        while (num > 0) {
            count[num % 10]++;
            num /= 10;
        }
    }

    // 输出每个数字出现的次数
    for (int i = 0; i < 10; i++) {
        printf("%d ", count[i]);
    }

    return 0;
}