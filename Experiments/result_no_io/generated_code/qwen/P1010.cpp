#include <stdio.h>

void printPower(int n) {
    if (n == 0) {
        printf("2(0)");
    } else if (n == 1) {
        printf("2");
    } else if ((n & (n - 1)) == 0) {
        int exp = 0;
        while (n > 1) {
            n >>= 1;
            exp++;
        }
        printf("2(%d)", exp);
    } else {
        int highestBit = 1 << 30;
        for (int i = 30; i >= 0; i--) {
            if (highestBit & n) {
                printPower(n >> i);
                break;
            }
            highestBit >>= 1;
        }
        printf("+");
        printPower(n & ((1 << i) - 1));
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printPower(n);
    return 0;
}