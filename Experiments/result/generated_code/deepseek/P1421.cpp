#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    int total_cents = a * 10 + b;
    int price_per_pen = 19;
    
    int max_pens = total_cents / price_per_pen;
    
    printf("%d\n", max_pens);
    
    return 0;
}