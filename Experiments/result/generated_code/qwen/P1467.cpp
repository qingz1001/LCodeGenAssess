#include <stdio.h>
#include <stdbool.h>

bool isRunaroundNumber(unsigned long long num) {
    if (num == 0) return false;
    unsigned long long originalNum = num;
    int digits[10];
    bool used[10] = {false};
    int count = 0;

    while (num > 0) {
        int digit = num % 10;
        if (digit == 0 || used[digit]) return false;
        digits[count++] = digit;
        used[digit] = true;
        num /= 10;
    }

    for (int i = 0; i < count; ++i) {
        num = originalNum;
        for (int j = 0; j < digits[i]; ++j) {
            num = (num % 10) * 10 + num / 1000000000;
        }
        if (num != originalNum && !used[num % 10]) return false;
    }

    return true;
}

unsigned long long findNextRunaroundNumber(unsigned long long m) {
    while (true) {
        m++;
        if (isRunaroundNumber(m)) {
            return m;
        }
    }
}

int main() {
    unsigned long long m;
    scanf("%llu", &m);
    printf("%llu\n", findNextRunaroundNumber(m));
    return 0;
}