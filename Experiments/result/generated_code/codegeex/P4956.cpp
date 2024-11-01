#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    // 每周的总收入
    int weekly_income = 4 * 100; // 每周4天，每天100
    // 总共52周
    int total_income = weekly_income * 52;

    // 遍历所有可能的x值
    for (int x = 100; x >= 1; x--) {
        // 剩余需要筹集的金额
        int remaining = n - total_income * x;
        // 每周每天的差额
        int daily_difference = remaining / 52;
        // 如果正好整除且daily_difference大于0
        if (remaining % 52 == 0 && daily_difference > 0) {
            printf("%d\n%d\n", x, daily_difference);
            return 0;
        }
    }

    return 0;
}