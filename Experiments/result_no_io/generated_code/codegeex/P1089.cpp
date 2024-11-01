#include <stdio.h>

int main() {
    int budget[12], savings = 0, money = 0, month;
    
    // 读取每个月的预算
    for (month = 0; month < 12; month++) {
        scanf("%d", &budget[month]);
    }
    
    // 模拟每个月的储蓄计划
    for (month = 0; month < 12; month++) {
        money += 300;  // 每月初收到300元
        if (money < budget[month]) {
            printf("-%d", month + 1);  // 如果钱不够用，输出月份并结束
            return 0;
        }
        money -= budget[month];  // 扣除当月预算
        savings += (money / 100) * 100;  // 存入整百的钱
        money %= 100;  // 剩余的钱
    }
    
    // 计算年末的总金额
    savings += savings * 0.2;  // 加上20%的利息
    printf("%d", savings);  // 输出年末总金额
    
    return 0;
}