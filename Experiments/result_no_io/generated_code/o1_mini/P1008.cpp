#include <stdio.h>

int main() {
    int A, B, C;
    for (A = 123; A <= 329; A++) {
        B = 2 * A;
        C = 3 * A;
        if (B > 987 || C > 987) continue;
        
        int digits[10] = {0};
        int num = A, valid = 1;
        while (num > 0) {
            int d = num % 10;
            if (d == 0 || digits[d]) { valid = 0; break; }
            digits[d] = 1;
            num /= 10;
        }
        if (!valid) continue;
        
        num = B;
        while (num > 0) {
            int d = num % 10;
            if (d == 0 || digits[d]) { valid = 0; break; }
            digits[d] = 1;
            num /= 10;
        }
        if (!valid) continue;
        
        num = C;
        while (num > 0) {
            int d = num % 10;
            if (d == 0 || digits[d]) { valid = 0; break; }
            digits[d] = 1;
            num /= 10;
        }
        if (!valid) continue;
        
        printf("%d %d %d\n", A, B, C);
    }
    return 0;
}