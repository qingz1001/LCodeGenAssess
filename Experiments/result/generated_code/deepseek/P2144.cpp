#include <stdio.h>
#include <string.h>

#define MAXN 101
#define MAXL 200

typedef struct {
    int len;
    int d[MAXL];
} BigInt;

void add(BigInt *a, BigInt *b, BigInt *c) {
    int carry = 0;
    c->len = a->len > b->len ? a->len : b->len;
    for (int i = 0; i < c->len; i++) {
        c->d[i] = a->d[i] + b->d[i] + carry;
        carry = c->d[i] / 10;
        c->d[i] %= 10;
    }
    if (carry) {
        c->d[c->len++] = carry;
    }
}

void mul(BigInt *a, int b, BigInt *c) {
    int carry = 0;
    c->len = a->len;
    for (int i = 0; i < c->len; i++) {
        c->d[i] = a->d[i] * b + carry;
        carry = c->d[i] / 10;
        c->d[i] %= 10;
    }
    while (carry) {
        c->d[c->len++] = carry % 10;
        carry /= 10;
    }
}

void printBigInt(BigInt *a) {
    for (int i = a->len - 1; i >= 0; i--) {
        printf("%d", a->d[i]);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    BigInt dp[MAXN];
    memset(dp, 0, sizeof(dp));
    dp[1].len = 1;
    dp[1].d[0] = 1;
    dp[2].len = 1;
    dp[2].d[0] = 5;

    for (int i = 3; i <= n; i++) {
        BigInt temp1, temp2;
        memset(&temp1, 0, sizeof(temp1));
        memset(&temp2, 0, sizeof(temp2));

        mul(&dp[i-1], 3, &temp1);
        add(&temp1, &dp[i-2], &temp2);
        dp[i] = temp2;
    }

    printBigInt(&dp[n]);

    return 0;
}