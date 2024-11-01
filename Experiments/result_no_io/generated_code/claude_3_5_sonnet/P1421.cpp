#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    int total_money = a * 10 + b;
    int pen_price = 19;
    
    int max_pens = total_money / pen_price;
    
    printf("%d\n", max_pens);
    
    return 0;
}