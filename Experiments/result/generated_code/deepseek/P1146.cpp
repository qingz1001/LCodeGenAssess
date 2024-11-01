#include <stdio.h>

void flipCoins(int N) {
    int coins[N];
    for (int i = 0; i < N; i++) {
        coins[i] = 0; // 初始化所有硬币为正面朝上
    }

    printf("%d\n", N); // 输出最少需要的操作次数

    for (int i = 0; i < N; i++) {
        // 每次翻转除了第 i 枚硬币之外的所有硬币
        for (int j = 0; j < N; j++) {
            if (j != i) {
                coins[j] = 1 - coins[j]; // 翻转硬币
            }
        }

        // 输出当前硬币状态
        for (int j = 0; j < N; j++) {
            printf("%d", coins[j]);
        }
        printf("\n");
    }
}

int main() {
    int N;
    scanf("%d", &N);
    flipCoins(N);
    return 0;
}