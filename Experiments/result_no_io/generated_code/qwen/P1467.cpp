#include <stdio.h>
#include <stdbool.h>

bool isRunaroundNumber(unsigned long long num) {
    if (num % 10 == 0) return false;

    unsigned long long original = num;
    int digits[10] = {0};
    int count = 0;

    while (num > 0) {
        int digit = num % 10;
        if (digits[digit]) return false;
        digits[digit]++;
        num /= 10;
        count++;
    }

    int step = original % count;
    unsigned long long current = original;
    for (int i = 0; i < count; i++) {
        current /= 10;
    }
    current %= 10;

    for (int i = 0; i < step - 1; i++) {
        current = current * 10 + original / count % 10;
        original /= 10;
    }

    return current == original % 10;
}

unsigned long long findNextRunaroundNumber(unsigned long long m) {
    unsigned long long next = m + 1;
    while (!isRunaroundNumber(next)) {
        next++;
    }
    return next;
}

int main() {
    unsigned long long m;
    scanf("%llu", &m);
    printf("%llu\n", findNextRunaroundNumber(m));
    return 0;
}