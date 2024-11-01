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

    int c = gcd(a, b);
    int pa = b / c;
    int pb = (a / c) + (b / c) - 1;

    printf("%d\n", c);
    printf("%d %d\n", pa, pb);

    return 0;
}