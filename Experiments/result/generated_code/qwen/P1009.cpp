#include <stdio.h>
#include <stdlib.h>

#define MAXN 60
#define BASE 1000000000

int main() {
    int n;
    scanf("%d", &n);

    int *factorial = (int *)malloc(MAXN * sizeof(int));
    for (int i = 0; i < MAXN; i++) {
        factorial[i] = 0;
    }
    factorial[0] = 1;

    int len = 1;
    for (int i = 2; i <= n; i++) {
        int carry = 0;
        for (int j = 0; j < len; j++) {
            long long product = (long long)factorial[j] * i + carry;
            factorial[j] = product % BASE;
            carry = product / BASE;
        }
        while (carry > 0) {
            factorial[len++] = carry % BASE;
            carry /= BASE;
        }
    }

    for (int i = len - 1; i >= 0; i--) {
        printf("%d", factorial[i]);
    }
    printf("\n");

    free(factorial);
    return 0;
}