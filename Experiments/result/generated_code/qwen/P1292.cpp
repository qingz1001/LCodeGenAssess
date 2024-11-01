#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    if (b == 0) {
        printf("0\n");
        printf("0 0\n");
        return 0;
    }

    int g = gcd(a, b);
    int c = a - (a / g * b);
    int P_a = a / g;
    int P_b = (a / g) * (a / g - 1) / 2;

    printf("%d\n", c);
    printf("%d %d\n", P_a, P_b);

    return 0;
}