#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 10001

typedef struct {
    int digits[MAX_DIGITS];
    int len;
} BigInt;

void initBigInt(BigInt *num, int value) {
    memset(num->digits, 0, sizeof(num->digits));
    num->len = 0;
    while (value > 0) {
        num->digits[num->len++] = value % 10;
        value /= 10;
    }
}

void subtract(BigInt *a, BigInt *b) {
    int carry = 0;
    for (int i = 0; i < a->len || i < b->len; i++) {
        a->digits[i] -= b->digits[i] + carry;
        if (a->digits[i] < 0) {
            a->digits[i] += 10;
            carry = 1;
        } else {
            carry = 0;
        }
    }
    while (a->len > 1 && a->digits[a->len - 1] == 0) {
        a->len--;
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

int countWeights(BigInt *m, int n) {
    int count = 0;
    BigInt weight;
    initBigInt(&weight, 1);

    while (compare(m, &weight) >= 0) {
        subtract(m, &weight);
        count++;

        // Multiply weight by n
        int carry = 0;
        for (int i = 0; i < weight.len; i++) {
            int temp = weight.digits[i] * n + carry;
            weight.digits[i] = temp % 10;
            carry = temp / 10;
        }
        while (carry > 0) {
            weight.digits[weight.len++] = carry % 10;
            carry /= 10;
        }
    }

    return count;
}

int main() {
    char m_str[MAX_DIGITS];
    int n;
    scanf("%s", m_str);
    scanf("%d", &n);

    BigInt m;
    m.len = strlen(m_str);
    for (int i = 0; i < m.len; i++) {
        m.digits[i] = m_str[m.len - 1 - i] - '0';
    }

    int result = countWeights(&m, n);
    printf("%d\n", result);

    return 0;
}