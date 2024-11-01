#include <stdio.h>

int main() {
    int N, reversed = 0;
    scanf("%d", &N);
    
    while (N != 0) {
        int digit = N % 10;
        if (reversed == 0 && digit == 0) {
            // Skip leading zeros
            N /= 10;
            continue;
        }
        reversed = reversed * 10 + digit;
        N /= 10;
    }
    
    printf("%d\n", reversed);
    return 0;
}