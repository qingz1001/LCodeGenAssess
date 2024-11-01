#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 200

void multiply(int result[], int n) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        int product = result[i] * n + carry;
        result[i] = product % 10;
        carry = product / 10;
    }
}

void add(int result[], int addend[]) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        int sum = result[i] + addend[i] + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int result[MAX_DIGITS] = {0};
    int temp[MAX_DIGITS] = {0};

    result[0] = 2;
    temp[0] = 1;

    for (int i = 1; i < n; i++) {
        multiply(result, 2);
        add(result, temp);
        memcpy(temp, result, sizeof(temp));
    }

    int start = MAX_DIGITS - 1;
    while (start > 0 && result[start] == 0) {
        start--;
    }

    for (int i = start; i >= 0; i--) {
        printf("%d", result[i]);
    }
    printf("\n");

    return 0;
}