#include <stdio.h>
#include <string.h>

int main() {
    int N;
    scanf("%d", &N);
    printf("%d\n", N);

    // 初始化所有硬币为正面朝上（0）
    int coins[N];
    for (int i = 0; i < N; i++) {
        coins[i] = 0;
    }

    // 每次翻转一个硬币
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j != i) {
                coins[j] = 1 - coins[j];
            }
        }
        // 输出当前硬币状态
        for (int j = 0; j < N; j++) {
            printf("%d", coins[j]);
        }
        printf("\n");
    }

    return 0;
}