#include <stdio.h>
#include <math.h>

int main() {
    int c;
    scanf("%d", &c);

    for (int a = 1; a <= c / 2; a++) {
        double b_squared = c * c - a * a;
        int b = sqrt(b_squared);
        if (b * b == b_squared) {
            printf("%d %d\n", a, b);
            return 0;
        }
    }

    return 0;
}