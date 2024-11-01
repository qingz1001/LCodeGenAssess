#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 50

void convertToBase(int n, int base) {
    char result[MAX_LEN];
    int index = 0;
    int isNegative = (n < 0);
    if (isNegative) n = -n;

    do {
        int remainder = n % base;
        if (remainder < 10) {
            result[index++] = '0' + remainder;
        } else {
            result[index++] = 'A' + (remainder - 10);
        }
        n /= base;
    } while (n > 0);

    if (isNegative) result[index++] = '-';

    for (int i = index - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }

    printf("=base-%d\n", abs(base));
}

int main() {
    int n, base;
    while (scanf("%d %d", &n, &base) != EOF) {
        convertToBase(n, base);
    }
    return 0;
}