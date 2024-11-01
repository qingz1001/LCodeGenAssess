#include <stdio.h>

int main() {
    int R1, S;
    scanf("%d %d", &R1, &S);

    // 根据公式 R2 = 2 * S - R1 计算R2
    int R2 = 2 * S - R1;
    printf("%d\n", R2);

    return 0;
}