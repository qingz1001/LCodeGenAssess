#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    int total_cents = a * 10 + b;
    int pen_cost = 19; // 1元9角转换为分
    int max_pens = total_cents / pen_cost;
    printf("%d\n", max_pens);
    return 0;
}