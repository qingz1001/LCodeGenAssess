#include <stdio.h>

int main() {
    int budget[12];
    int savings = 0;
    int pocket = 0;
    
    // 读取12个月的预算
    for (int i = 0; i < 12; i++) {
        scanf("%d", &budget[i]);
    }
    
    // 模拟12个月的储蓄计划
    for (int month = 0; month < 12; month++) {
        pocket += 300; // 每月初妈妈给的零花钱
        
        if (pocket < budget[month]) {
            // 如果钱不够用，输出负数月份并退出
            printf("-%d\n", month + 1);
            return 0;
        }
        
        pocket -= budget[month]; // 减去当月预算
        
        // 将整百的钱存入妈妈处
        int toSave = (pocket / 100) * 100;
        savings += toSave;
        pocket -= toSave;
    }
    
    // 计算年末总金额
    int total = pocket + savings + (savings / 5);
    printf("%d\n", total);
    
    return 0;
}