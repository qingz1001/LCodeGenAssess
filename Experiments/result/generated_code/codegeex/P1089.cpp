#include <stdio.h>

int main() {
    int budget[12];
    int savings = 0;
    int monthly_income = 300;

    // 读取每个月的预算
    for (int i = 0; i < 12; i++) {
        scanf("%d", &budget[i]);
    }

    // 遍历每个月
    for (int i = 0; i < 12; i++) {
        int remaining = monthly_income - budget[i];

        // 如果剩余的钱不够用，输出负的当前月份并结束程序
        if (remaining < 0) {
            printf("-%d\n", i + 1);
            return 0;
        }

        // 存入整百的钱
        savings += remaining / 100 * 100;

        // 更新剩余的钱
        remaining %= 100;
        monthly_income += 300;
    }

    // 计算年末总金额
    int total_amount = savings * 1.2 + monthly_income;

    // 输出结果
    printf("%d\n", total_amount);

    return 0;
}