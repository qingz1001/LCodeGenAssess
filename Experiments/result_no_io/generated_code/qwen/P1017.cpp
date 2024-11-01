#include <stdio.h>
#include <stdlib.h>

void printNumber(int num, int base) {
    if (num == 0) {
        printf("0");
        return;
    }

    char digits[37];
    int index = 0;

    while (num != 0) {
        int remainder = abs(num % base);
        if (remainder >= 10) {
            digits[index++] = 'A' + (remainder - 10);
        } else {
            digits[index++] = '0' + remainder;
        }
        num /= base;
    }

    for (int i = index - 1; i >= 0; i--) {
        printf("%c", digits[i]);
    }
}

int main() {
    int n, R;
    while (scanf("%d %d", &n, &R) != EOF) {
        printf("(%d)%d\n", n, R);
        printNumber(n, R);
        printf("\n");
    }
    return 0;
}