#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 10

int magic(int n) {
    if (n < 10) return n;
    
    char num[MAX_DIGITS + 1];
    sprintf(num, "%d", n);
    int len = strlen(num);
    
    int result = 0;
    for (int i = 1; i < len; i++) {
        int diff = abs(num[i] - num[i-1]);
        result = result * 10 + diff;
    }
    
    return result;
}

int magic_fingerprint(int n) {
    while (n >= 10) {
        n = magic(n);
    }
    return n;
}

int main() {
    int A, B;
    scanf("%d", &A);
    scanf("%d", &B);
    
    int lucky_count = 0;
    for (int i = A; i <= B; i++) {
        if (magic_fingerprint(i) == 7) {
            lucky_count++;
        }
    }
    
    printf("%d\n", lucky_count);
    
    return 0;
}