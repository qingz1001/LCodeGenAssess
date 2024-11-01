#include <stdio.h>
#include <stdlib.h>

int magic(int n) {
    while (n >= 10) {
        int new_n = 0;
        int factor = 1;
        int last_digit = n % 10;
        n /= 10;
        while (n > 0) {
            int current_digit = n % 10;
            int diff = abs(current_digit - last_digit);
            new_n += diff * factor;
            factor *= 10;
            last_digit = current_digit;
            n /= 10;
        }
        n = new_n;
    }
    return n;
}

int main() {
    long long A, B;
    if (scanf("%lld", &A) != 1) return 1;
    if (scanf("%lld", &B) != 1) return 1;
    
    long long count = 0;
    for(long long n = A; n <= B; n++) {
        if(magic((int)n) == 7) {
            count++;
        }
    }
    printf("%lld\n", count);
    return 0;
}