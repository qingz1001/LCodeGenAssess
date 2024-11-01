#include <stdio.h>

void printPower(int n) {
    if (n == 0) {
        printf("2(0)");
        return;
    }
    if (n == 1) {
        printf("2");
        return;
    }
    int highestPower = 1;
    while ((1 << highestPower) <= n) {
        highestPower++;
    }
    highestPower--;
    
    printf("2(");
    printPower(highestPower);
    n -= (1 << highestPower);
    while (n > 0) {
        int nextPower = 1;
        while ((1 << nextPower) <= n) {
            nextPower++;
        }
        nextPower--;
        printf("+");
        printPower(nextPower);
        n -= (1 << nextPower);
    }
    printf(")");
}

int main() {
    int n;
    scanf("%d", &n);
    printPower(n);
    return 0;
}