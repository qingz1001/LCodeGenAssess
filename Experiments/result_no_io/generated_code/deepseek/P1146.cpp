#include <stdio.h>

void flipCoins(int N) {
    int S = N; // 最少需要的操作次数为 N
    printf("%d\n", S);

    // 初始状态全为 0
    for (int i = 0; i < N; i++) {
        printf("0");
    }
    printf("\n");

    // 每次翻转 N-1 枚硬币
    for (int i = 0; i < N; i++) {
        // 翻转除了第 i 枚硬币之外的所有硬币
        for (int j = 0; j < N; j++) {
            if (j == i) {
                printf("0"); // 不翻转第 i 枚硬币
            } else {
                printf("1"); // 翻转其他硬币
            }
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