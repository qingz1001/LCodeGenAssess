#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    // 将元和角转换为总的角数
    int totalCents = a * 10 + b;

    // 一支笔的价格为19角
    int penPrice = 19;

    // 计算最多能买多少支笔
    int maxPens = totalCents / penPrice;

    printf("%d\n", maxPens);

    return 0;
}