#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 200

typedef struct {
    int digits[MAX_DIGITS];
    int len;
} BigInt;

void initBigInt(BigInt *num) {
    memset(num->digits, 0, sizeof(num->digits));
    num->len = 1;
}

void addBigInt(BigInt *a, BigInt *b, BigInt *result) {
    int carry = 0;
    int maxLen = a->len > b->len ? a->len : b->len;
    result->len = maxLen;

    for (int i = 0; i < maxLen; i++) {
        int sum = a->digits[i] + b->digits[i] + carry;
        result->digits[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry) {
        result->digits[maxLen] = carry;
        result->len++;
    }
}

void printBigInt(BigInt *num) {
    for (int i = num->len - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
}

int main() {
    int k, w;
    scanf("%d %d", &k, &w);

    int maxDigit = 1 << k; // 2^k
    int maxBits = w / k;
    int remainingBits = w % k;

    BigInt dp[maxDigit];
    BigInt result;
    initBigInt(&result);

    for (int i = 0; i < maxDigit; i++) {
        initBigInt(&dp[i]);
    }

    dp[0].digits[0] = 1;

    for (int i = 1; i < maxDigit; i++) {
        for (int j = i; j < maxDigit; j++) {
            BigInt temp;
            initBigInt(&temp);
            addBigInt(&dp[j], &dp[j - i], &temp);
            memcpy(&dp[j], &temp, sizeof(BigInt));
        }
    }

    for (int i = 2; i <= maxBits; i++) {
        BigInt temp;
        initBigInt(&temp);
        addBigInt(&dp[maxDigit - 1], &result, &temp);
        memcpy(&result, &temp, sizeof(BigInt));
    }

    if (remainingBits > 0) {
        int maxRemaining = 1 << remainingBits;
        for (int i = 1; i < maxRemaining; i++) {
            BigInt temp;
            initBigInt(&temp);
            addBigInt(&dp[maxDigit - 1 - i], &result, &temp);
            memcpy(&result, &temp, sizeof(BigInt));
        }
    }

    printBigInt(&result);

    return 0;
}