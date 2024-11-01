#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 200

void add(int *a, int *b, int *c) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        c[i] = a[i] + b[i] + carry;
        carry = c[i] / 10;
        c[i] %= 10;
    }
}

void subtract(int *a, int *b, int *c) {
    int borrow = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        c[i] = a[i] - b[i] - borrow;
        if (c[i] < 0) {
            c[i] += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
    }
}

void multiply(int *a, int b, int *c) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        c[i] = a[i] * b + carry;
        carry = c[i] / 10;
        c[i] %= 10;
    }
}

void copy(int *a, int *b) {
    for (int i = 0; i < MAX_DIGITS; i++) {
        a[i] = b[i];
    }
}

void init(int *a) {
    for (int i = 0; i < MAX_DIGITS; i++) {
        a[i] = 0;
    }
}

void print(int *a) {
    int start = MAX_DIGITS - 1;
    while (start > 0 && a[start] == 0) start--;
    for (int i = start; i >= 0; i--) {
        printf("%d", a[i]);
    }
    printf("\n");
}

int main() {
    int k, w;
    scanf("%d %d", &k, &w);

    int max_digits = (w + k - 1) / k;
    int max_value = 1 << k;

    int dp[max_digits + 1][MAX_DIGITS];
    int temp[MAX_DIGITS];
    int result[MAX_DIGITS];

    init(result);

    for (int i = 0; i <= max_digits; i++) {
        init(dp[i]);
    }

    dp[0][0] = 1;

    for (int i = 1; i <= max_digits; i++) {
        for (int j = 1; j < max_value; j++) {
            init(temp);
            for (int l = j + 1; l < max_value; l++) {
                add(dp[i - 1], dp[i - 1], temp);
            }
            add(dp[i], temp, dp[i]);
        }
    }

    for (int i = 2; i <= max_digits; i++) {
        add(result, dp[i], result);
    }

    print(result);

    return 0;
}