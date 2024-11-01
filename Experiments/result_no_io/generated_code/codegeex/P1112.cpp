#include <stdio.h>

int isWaveNumber(int num, int base) {
    int prev_digit = -1;
    int wave_count = 0;

    while (num > 0) {
        int digit = num % base;
        if (digit == prev_digit) {
            return 0;
        }
        if (prev_digit != -1) {
            wave_count++;
        }
        prev_digit = digit;
        num /= base;
    }

    return wave_count;
}

int isKWaveNumber(int num, int k, int l, int r) {
    for (int base = l; base <= r; base++) {
        if (isWaveNumber(num, base) < k) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int l, r, L, R, k;
    scanf("%d %d %d %d %d", &l, &r, &L, &R, &k);

    for (int num = L; num <= R; num++) {
        if (isKWaveNumber(num, k, l, r)) {
            printf("%d\n", num);
        }
    }

    return 0;
}