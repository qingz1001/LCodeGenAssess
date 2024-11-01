#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 10001

typedef struct {
    int digits[MAX_DIGITS];
    int len;
} BigInt;

void initBigInt(BigInt *num, const char *str) {
    num->len = strlen(str);
    for (int i = 0; i < num->len; i++) {
        num->digits[i] = str[num->len - 1 - i] - '0';
    }
}

int compare(BigInt *a, BigInt *b) {
    if (a->len > b->len) return 1;
    if (a->len < b->len) return -1;
    for (int i = a->len - 1; i >= 0; i--) {
        if (a->digits[i] > b->digits[i]) return 1;
        if (a->digits[i] < b->digits[i]) return -1;
    }
    return 0;
}

void subtract(BigInt *a, BigInt *b) {
    int borrow = 0;
    for (int i = 0; i < a->len; i++) {
        a->digits[i] -= (i < b->len ? b->digits[i] : 0) + borrow;
        if (a->digits[i] < 0) {
            a->digits[i] += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
    }
    while (a->len > 1 && a->digits[a->len - 1] == 0) a->len--;
}

void divideByInt(BigInt *a, int n) {
    int carry = 0;
    for (int i = a->len - 1; i >= 0; i--) {
        int temp = a->digits[i] + carry * 10;
        a->digits[i] = temp / n;
        carry = temp % n;
    }
    while (a->len > 1 && a->digits[a->len - 1] == 0) a->len--;
}

int main() {
    char m_str[MAX_DIGITS];
    int n;
    scanf("%s %d", m_str, &n);

    BigInt m;
    initBigInt(&m, m_str);

    int count = 0;
    while (m.len > 1 || m.digits[0] > 0) {
        int remainder = m.digits[0] % n;
        if (remainder != 0) {
            count++;
        }
        divideByInt(&m, n);
    }

    printf("%d\n", count);
    return 0;
}