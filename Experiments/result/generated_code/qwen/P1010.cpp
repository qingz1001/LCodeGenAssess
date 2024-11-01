#include <stdio.h>

void printPower(int n) {
    if (n == 0) {
        printf("2(0)");
        return;
    }
    int highestPower = 0;
    for (int i = 1; i <= n; i <<= 1) {
        highestPower++;
    }
    highestPower--;
    printf("2(%d", highestPower);
    int remaining = n - (1 << highestPower);
    if (remaining > 0) {
        printf("+");
        printPower(remaining);
    }
    printf(")");
}

int main() {
    int n;
    scanf("%d", &n);
    printPower(n);
    return 0;
}