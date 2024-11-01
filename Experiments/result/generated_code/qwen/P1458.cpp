#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void printFractions(int n) {
    for (int b = 1; b <= n; b++) {
        for (int a = 0; a <= b; a++) {
            if (gcd(a, b) == 1) {
                printf("%d/%d\n", a, b);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printFractions(n);
    return 0;
}