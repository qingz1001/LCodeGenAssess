#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_DIGITS 1000000

void multiply_by_2(int *num, int *len) {
    int carry = 0;
    for (int i = 0; i < *len || carry; i++) {
        if (i == *len) (*len)++;
        int temp = num[i] * 2 + carry;
        num[i] = temp % 10;
        carry = temp / 10;
    }
}

void subtract_one(int *num, int len) {
    for (int i = 0; i < len; i++) {
        if (num[i] > 0) {
            num[i]--;
            break;
        }
        num[i] = 9;
    }
}

int main() {
    int P;
    scanf("%d", &P);

    int num[MAX_DIGITS] = {0};
    num[0] = 1;
    int len = 1;

    for (int i = 0; i < P; i++) {
        multiply_by_2(num, &len);
    }

    subtract_one(num, len);

    // Calculate and print the number of digits
    printf("%d\n", len);

    // Print the last 500 digits
    int start = (len > 500) ? len - 500 : 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 50; j++) {
            if (start + 49 - j + i * 50 < len) {
                printf("%d", num[start + 49 - j + i * 50]);
            } else {
                printf("0");
            }
        }
        printf("\n");
    }

    return 0;
}