#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);

    int S = N; // 最少需要的操作次数
    printf("%d\n", S);

    // 初始状态，所有硬币正面朝上（0）
    for (int i = 0; i < N; i++) {
        printf("0 ");
    }
    printf("\n");

    // 每次翻转所有硬币，直到所有硬币反面朝上（1）
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j != i) {
                printf("1 ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }

    return 0;
}