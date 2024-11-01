#include <stdio.h>
#include <stdbool.h>

bool is_wave_number(int num, int base) {
    int prev = num % base;
    num /= base;
    while (num > 0) {
        int curr = num % base;
        if (curr == prev) return false;
        prev = curr;
        num /= base;
    }
    return true;
}

bool is_k_wave_number(int num, int l, int r, int k) {
    int count = 0;
    for (int base = l; base <= r; base++) {
        if (is_wave_number(num, base)) {
            count++;
            if (count >= k) return true;
        }
    }
    return false;
}

int main() {
    int l, r, L, R, k;
    scanf("%d %d %d %d %d", &l, &r, &L, &R, &k);

    for (int num = L; num <= R; num++) {
        if (is_k_wave_number(num, l, r, k)) {
            printf("%d\n", num);
        }
    }

    return 0;
}