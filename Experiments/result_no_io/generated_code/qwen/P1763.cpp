#include <stdio.h>

void egyptianFraction(int numerator, int denominator) {
    if (denominator % numerator == 0) {
        printf("%d ", denominator / numerator);
        return;
    }
    int firstUnit = denominator / numerator + 1;
    int remainder = numerator * firstUnit - denominator;
    printf("%d ", firstUnit);
    egyptianFraction(remainder, denominator * firstUnit);
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    egyptianFraction(a, b);
    printf("\n");
    return 0;
}