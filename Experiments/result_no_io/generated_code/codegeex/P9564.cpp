#include <stdio.h>

int main() {
    int A, B;
    scanf("%d%d", &A, &B);

    // 骰子的点数和的范围
    int min = (A + B) / 3; // 最小的点数和
    int max = (A + B) / 1; // 最大的点数和

    // 检查是否存在三只骰子的点数和满足条件
    if (min <= 6 && max >= 6) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}