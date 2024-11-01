#include <stdio.h>

void printPower(int n) {
    if (n == 0) {
        printf("0");
        return;
    }
    if (n == 1) {
        printf("2(0)");
        return;
    }
    int power = 1;
    while (power <= n) {
        power *= 2;
    }
    power /= 2;
    printPower(power);
    printf("+");
    if (power == n) {
        printf("2(0)");
    } else {
        printPower(n - power);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printPower(n);
    return 0;
}