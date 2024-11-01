#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void decimalToNegativeBase(int n, int r) {
    char result[MAX_LEN] = {0};
    int index = 0;

    if (n == 0) {
        printf("0 (%d)\n", r);
        return;
    }

    while (n != 0) {
        int remainder = n % r;
        n = n / r;

        if (remainder < 0) {
            remainder += -r;
            n += 1;
        }

        if (remainder < 10) {
            result[index++] = remainder + '0';
        } else {
            result[index++] = remainder - 10 + 'A';
        }
    }

    result[index] = '\0';
    reverseString(result);

    printf("%s (%d)\n", result, r);
}

int main() {
    int n, r;
    
    while (scanf("%d %d", &n, &r) == 2) {
        decimalToNegativeBase(n, r);
    }

    return 0;
}