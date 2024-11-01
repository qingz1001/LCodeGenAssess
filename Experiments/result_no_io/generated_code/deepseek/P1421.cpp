#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    // 将所有的钱转换为角
    int total_money_in_cents = a * 10 + b;
    
    // 每支签字笔的价格是1元9角，即19角
    int pen_price_in_cents = 19;
    
    // 计算最多能买多少支签字笔
    int max_pens = total_money_in_cents / pen_price_in_cents;
    
    printf("%d\n", max_pens);
    
    return 0;
}