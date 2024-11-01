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

    int c = a % b;
    if (c == 0) {
        printf("0\n0 0\n");
        return 0;
    }

    int g = gcd(a, b);
    c = c / g;
    b = b / g;

    int Pa = 0, Pb = 0;
    while (c % 2 == 0) {
        c /= 2;
        Pa++;
    }
    while (c % 3 == 0) {
        c /= 3;
        Pb++;
    }

    if (c != 1) {
        printf("0\n0 0\n");
    } else {
        printf("%d\n%d %d\n", g, Pa, Pb);
    }

    return 0;
}