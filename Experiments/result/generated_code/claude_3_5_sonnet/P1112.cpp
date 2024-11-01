#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DIGITS 32

bool is_wave_number(int num, int base) {
    if (num < 10) return true;
    
    int digits[MAX_DIGITS];
    int len = 0;
    
    while (num > 0) {
        digits[len++] = num % base;
        num /= base;
    }
    
    for (int i = 2; i < len; i++) {
        if (digits[i] != digits[i % 2]) {
            return false;
        }
    }
    
    return digits[0] != digits[1];
}

int main() {
    int l, r, L, R, k;
    scanf("%d %d %d %d %d", &l, &r, &L, &R, &k);
    
    for (int num = L; num <= R; num++) {
        int count = 0;
        for (int base = l; base <= r; base++) {
            if (is_wave_number(num, base)) {
                count++;
            }
        }
        if (count == k) {
            printf("%d\n", num);
        }
    }
    
    return 0;
}