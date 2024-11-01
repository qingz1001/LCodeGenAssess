#include <stdio.h>
#include <math.h>

int isWaveNumber(int num, int base, int k) {
    int prevDigit = -1;
    int count = 0;
    int digit;
    int numDigits = 0;
    while (num > 0) {
        digit = num % base;
        num /= base;
        numDigits++;
        if (prevDigit != -1 && prevDigit != digit) {
            count++;
            prevDigit = digit;
        } else {
            prevDigit = digit;
        }
    }
    return count == numDigits - 1 && count >= k;
}

int main() {
    int l, r, L, R, k;
    scanf("%d %d %d %d %d", &l, &r, &L, &R, &k);

    for (int num = L; num <= R; num++) {
        int isDoubleWave = 0;
        int isTripleWave = 0;
        int isQuadrupleWave = 0;

        for (int base = l; base <= r; base++) {
            if (isWaveNumber(num, base, k)) {
                if (k == 2) isDoubleWave = 1;
                if (k == 3) isTripleWave = 1;
                if (k == 4) isQuadrupleWave = 1;
            }
        }

        if ((k == 2 && isDoubleWave) ||
            (k == 3 && isTripleWave) ||
            (k == 4 && isQuadrupleWave)) {
            printf("%d\n", num);
        }
    }

    return 0;
}