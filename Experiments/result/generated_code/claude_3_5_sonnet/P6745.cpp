#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 501

void multiply(char* result, int multiplier) {
    int carry = 0;
    for (int i = strlen(result) - 1; i >= 0; i--) {
        int digit = (result[i] - '0') * multiplier + carry;
        result[i] = digit % 10 + '0';
        carry = digit / 10;
    }
    while (carry) {
        memmove(result + 1, result, strlen(result) + 1);
        result[0] = carry % 10 + '0';
        carry /= 10;
    }
}

void add(char* result, long long x) {
    int i = strlen(result) - 1;
    while (x > 0) {
        int digit = (result[i] - '0') + (x % 10);
        result[i] = digit % 10 + '0';
        x /= 10;
        int carry = digit / 10;
        i--;
        while (carry && i >= 0) {
            digit = (result[i] - '0') + carry;
            result[i] = digit % 10 + '0';
            carry = digit / 10;
            i--;
        }
        if (carry) {
            memmove(result + 1, result, strlen(result) + 1);
            result[0] = carry + '0';
        }
    }
}

int main() {
    int k;
    long long x;
    scanf("%d %lld", &k, &x);

    char result[MAX_DIGITS] = "1";
    for (int i = 0; i < k; i++) {
        multiply(result, 10);
    }
    
    add(result, x);

    printf("%s\n", result);

    return 0;
}