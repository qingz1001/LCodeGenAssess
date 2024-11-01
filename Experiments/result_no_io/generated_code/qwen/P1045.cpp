#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 1000000
#define CHUNK_SIZE 50

void multiply_by_2(char *num, int *length) {
    int carry = 0;
    for (int i = 0; i < *length; i++) {
        int product = num[i] * 2 + carry;
        num[i] = product % 10;
        carry = product / 10;
    }
    while (carry > 0) {
        num[*length] = carry % 10;
        carry /= 10;
        (*length)++;
    }
}

void subtract_one(char *num, int length) {
    for (int i = length - 1; i >= 0; i--) {
        if (num[i] == 0) {
            num[i] = 9;
        } else {
            num[i]--;
            break;
        }
    }
}

void print_number(const char *num, int length) {
    for (int i = length - 1; i >= 0; i--) {
        printf("%d", num[i]);
    }
    printf("\n");
}

int main() {
    int P;
    scanf("%d", &P);

    char *number = (char *)malloc(MAX_DIGITS * sizeof(char));
    number[0] = 1;
    int length = 1;

    for (int i = 0; i < P; i++) {
        multiply_by_2(number, &length);
    }

    subtract_one(number, length);

    // Calculate the number of digits
    int digit_count = 0;
    for (int i = 0; i < length; i++) {
        digit_count += (number[i] != 0 ? 1 : 0);
    }

    printf("%d\n", digit_count);

    // Print the last 500 digits
    for (int i = length - 1; i >= length - 500; i -= CHUNK_SIZE) {
        int end = i - CHUNK_SIZE + 1;
        if (end < 0) end = 0;
        for (int j = end; j <= i; j++) {
            printf("%d", number[j]);
        }
        printf("\n");
    }

    free(number);
    return 0;
}