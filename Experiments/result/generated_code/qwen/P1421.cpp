#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    int total_cents = a * 10 + b;
    int pen_price_cents = 19;
    int max_pens = total_cents / pen_price_cents;
    printf("%d\n", max_pens);
    return 0;
}