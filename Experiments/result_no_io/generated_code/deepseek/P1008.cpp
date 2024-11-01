#include <stdio.h>

int is_valid(int a, int b, int c) {
    int digits[10] = {0};
    while (a > 0) {
        digits[a % 10]++;
        a /= 10;
    }
    while (b > 0) {
        digits[b % 10]++;
        b /= 10;
    }
    while (c > 0) {
        digits[c % 10]++;
        c /= 10;
    }
    for (int i = 1; i <= 9; i++) {
        if (digits[i] != 1) return 0;
    }
    return 1;
}

int main() {
    for (int i = 123; i <= 329; i++) {
        int j = 2 * i;
        int k = 3 * i;
        if (is_valid(i, j, k)) {
            printf("%d %d %d\n", i, j, k);
        }
    }
    return 0;
}