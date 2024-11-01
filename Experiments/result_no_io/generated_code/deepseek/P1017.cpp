#include <stdio.h>
#include <string.h>

void decimalToNegativeBase(int n, int R) {
    char result[100];
    int index = 0;

    while (n != 0) {
        int remainder = n % R;
        n /= R;

        if (remainder < 0) {
            remainder -= R;
            n += 1;
        }

        if (remainder < 10) {
            result[index++] = remainder + '0';
        } else {
            result[index++] = remainder - 10 + 'A';
        }
    }

    if (index == 0) {
        result[index++] = '0';
    }

    result[index] = '\0';

    for (int i = index - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
    printf("(%d)\n", R);
}

int main() {
    int n, R;
    while (scanf("%d %d", &n, &R) != EOF) {
        decimalToNegativeBase(n, R);
    }
    return 0;
}