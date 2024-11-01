#include <stdio.h>

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    
    // 将元和角转换为总的角数
    int total_cents = a * 10 + b;
    
    // 每只签字笔的价格为19角
    int pen_price_cents = 19;
    
    // 计算最多能买多少只签字笔
    int max_pens = total_cents / pen_price_cents;
    
    // 输出结果
    printf("%d\n", max_pens);
    
    return 0;
}