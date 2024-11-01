#include <stdio.h>
#include <string.h>

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
    int len = 1;
    num[0] = 1;

    for (int i = 0; i < P; i++) {
        multiply_by_2(num, &len);
    }

    subtract_one(num, len);

    while (len > 0 && num[len-1] == 0) len--;

    printf("%d\n", len);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 50; j++) {
            if (len - 1 - (i * 50 + j) >= 0) {
                printf("%d", num[len - 1 - (i * 50 + j)]);
            } else {
                printf("0");
            }
        }
        printf("\n");
    }

    return 0;
}