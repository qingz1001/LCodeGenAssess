#include <stdio.h>
#include <string.h>

#define MAX_P 3100000
#define MAX_DIGITS 100000

char result[MAX_DIGITS];

void multiply(char *num, int multiplier) {
    int carry = 0;
    for (int i = 0; i < strlen(num); i++) {
        int product = (num[i] - '0') * multiplier + carry;
        num[i] = product % 10 + '0';
        carry = product / 10;
    }
    while (carry) {
        int product = carry + '0';
        num[strlen(num)] = product % 10 + '0';
        carry = product / 10;
    }
}

void shiftLeft(char *num) {
    for (int i = strlen(num) - 1; i >= 0; i--) {
        if (i > 0) {
            num[i] = num[i - 1];
        } else {
            num[i] = '0';
        }
    }
}

void power(int P) {
    strcpy(result, "2");
    for (int i = 1; i < P; i++) {
        multiply(result, 2);
        shiftLeft(result);
    }
}

int main() {
    int P;
    scanf("%d", &P);

    power(P);

    int digits = strlen(result);
    printf("%d\n", digits);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 50; j++) {
            if (digits - i * 50 - j - 1 >= 0) {
                printf("%c", result[digits - i * 50 - j - 1]);
            } else {
                printf("0");
            }
        }
        printf("\n");
    }

    return 0;
}